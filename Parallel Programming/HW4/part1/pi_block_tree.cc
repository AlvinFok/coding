#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
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
    // ---

    // TODO: MPI init
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    long long int loopPerRank = tosses / world_size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // printf("Rank = %d\n", world_rank);
    MPI_Status status;
    long long totalIn = 0;
    long long localTotal, recvTotal;
    localTotal = pi_cal(world_rank, loopPerRank);
    int round = 0;
    bool isEven = (world_rank%2==0)? true : false;
    int index = world_rank / pow(2, round);

    

    while(isEven){
        int src = (index + 1) * pow(2, round);
        
        MPI_Recv(&recvTotal, 1, MPI_LONG_LONG, src, 0, MPI_COMM_WORLD, &status);
        // printf("%d Recv from %d %lld\n", world_rank, src, recvTotal);
        localTotal += recvTotal;
        round++;
        index = world_rank / pow(2, round);
        isEven = (index%2==0) ? true : false;
        if(round >= log2(world_size))
            break;
    } 

    
    if(world_rank > 0){
        int dest = (index - 1) * pow(2, round);
        // printf("%d send to %d %lld\n", world_rank, dest, localTotal);
        MPI_Send(&localTotal, 1, MPI_LONG_LONG, dest, 0, MPI_COMM_WORLD);
    }
    

    // TODO: binary tree redunction

    if (world_rank == 0)
    {
        // TODO: PI result
        pi_result = 4 * ((double)localTotal / tosses);
        // --- DON'T TOUCH ---
        double end_time = MPI_Wtime();
        printf("%lf\n", pi_result);
        printf("MPI running time: %lf Seconds\n", end_time - start_time);
        // ---
    }

    MPI_Finalize();
    return 0;
}
