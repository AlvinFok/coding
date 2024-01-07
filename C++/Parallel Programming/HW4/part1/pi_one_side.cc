#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
unsigned int SEED;
inline void fastSrand(int seed, int rank){
    SEED = seed * rank;
}

inline int fastRand(){
    SEED = (214013*SEED+2531011);
    return (SEED>>16)&0x7FFF;
}

long long int pi_cal(int rank, long long numIter){
    long long total = 0;
    int x, y;
    int radius = 0x7FFF * 0x7FFF;
    // unsigned int seed = (long)rank;
    fastSrand((int)time(NULL), rank);
    
    for(long long i = 0; i < numIter; i++){
        x = fastRand();
        y = fastRand();
        if(x*x + y*y < radius){
            total++;
        }
    }

    return total;
}


int fnz (long long int *recvTotal, int size)
{
    int diff = 0;

    for (int i = 0; i < size; i++)
       diff |= (recvTotal[i] != 0);

    if (diff)
    {
       int res = 0;
       for (int i = 0; i < size; i++)
       {
          if(recvTotal[i] != 0)
            res++;
       }

       return(res == size-1);
    }
    return 0;
}

int main(int argc, char **argv)
{
    // --- DON'T TOUCH ---
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();
    double pi_result;
    long long int tosses = atoi(argv[1]);
    int world_rank, world_size;
    // ---

    MPI_Win win;

    // TODO: MPI init
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    long long int loopPerRank = tosses / world_size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    long long totalIn = 0;
    long long localTotal, recvTotal[world_size];
    if (world_rank == 0)
    {
        // Master
        long long *recvTotal;
        MPI_Alloc_mem(world_size * sizeof(long long), MPI_INFO_NULL, &recvTotal);
        for(int i = 0; i < world_size; i++){
            recvTotal[i] = 0;
        }

        localTotal = pi_cal(world_rank, loopPerRank);
        totalIn = localTotal;
        MPI_Win_create(recvTotal, world_size* sizeof(long long), sizeof(long long), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
        int ready = 0;
        while (!ready)
        {
            // Without the lock/unlock schedule stays forever filled with 0s
            MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, win);
            ready = fnz(recvTotal, world_size);
            MPI_Win_unlock(0, win);
        }
        for(int i = 0; i < world_size;i++){
            totalIn += recvTotal[i];
        }

        // Free the allocated memory
        MPI_Free_mem(recvTotal);
    }
    else
    {
        // Workers
        localTotal = pi_cal(world_rank, loopPerRank);

        // Worker processes do not expose memory in the window
        MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

        // Register with the master
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);
        MPI_Put(&localTotal, 1, MPI_LONG_LONG, 0, world_rank, 1, MPI_LONG_LONG, win);
        MPI_Win_unlock(0, win);

    
    }

    MPI_Win_free(&win);

    if (world_rank == 0)
    {
        // TODO: handle PI result
        pi_result = 4 *((double)totalIn/tosses);
        // --- DON'T TOUCH ---
        double end_time = MPI_Wtime();
        printf("%lf\n", pi_result);
        printf("MPI running time: %lf Seconds\n", end_time - start_time);
        // ---
    }
    
    MPI_Finalize();
    return 0;
}