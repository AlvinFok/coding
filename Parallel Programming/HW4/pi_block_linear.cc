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


int main(int argc, char **argv)
{
    // --- DON'T TOUCH ---
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();
    double pi_result;
    long long int tosses = atoi(argv[1]);
    int world_rank, world_size;
    MPI_Status status;
    // ---

    // TODO: init MPI
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    long long int loopPerRank = tosses / world_size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // printf("Rank = %d\n", world_rank);
    long long totalIn = 0;
    if (world_rank > 0)
    {
        long long int localTotal = pi_cal(world_rank, loopPerRank);
        // printf("%d send %lld\n", world_rank, localTotal);
        MPI_Send(&localTotal, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
        // TODO: handle workers
    }
    else if (world_rank == 0)
    {
        // TODO: master
        long long int localTotal = pi_cal(world_rank, loopPerRank);
        totalIn += localTotal;
        for(int i = 1; i < world_size;i++){
            MPI_Recv(&localTotal, 1, MPI_LONG_LONG, i, 0, MPI_COMM_WORLD, &status);
            // printf("recv %lld from %d\n", localTotal, i);
            totalIn += localTotal;
        }
    }

    if (world_rank == 0)
    {
        // TODO: process PI result
        printf("TotalIn = %lld\n",totalIn);
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
