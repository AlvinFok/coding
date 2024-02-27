#include <mpi.h>
#include <cstdio>
#include<iostream>

using namespace std;

#define FROM_MASTER 1
#define FROM_WORKER 2
int myRank, world_size, N, M, L;
int** a;
int** b;
int** c;
// *********************************************
// ** ATTENTION: YOU CANNOT MODIFY THIS FILE. **
// *********************************************

// Read size of matrix_a and matrix_b (n, m, l) and whole data of matrixes from stdin
//
// n_ptr:     pointer to n
// m_ptr:     pointer to m
// l_ptr:     pointer to l
// a_mat_ptr: pointer to matrix a (a should be a continuous memory space for placing n * m elements of int)
// b_mat_ptr: pointer to matrix b (b should be a continuous memory space for placing m * l elements of int)
void construct_matrices(int *n_ptr, int *m_ptr, int *l_ptr,
                        int **a_mat_ptr, int **b_mat_ptr);

// Just matrix multiplication (your should output the result in this function)
// 
// n:     row number of matrix a
// m:     col number of matrix a / row number of matrix b
// l:     col number of matrix b
// a_mat: a continuous memory placing n * m elements of int
// b_mat: a continuous memory placing m * l elements of int
void matrix_multiply(const int n, const int m, const int l,
                     const int *a_mat, const int *b_mat);

// Remember to release your allocated memory
void destruct_matrices(int *a_mat, int *b_mat);

int main () {
    int n, m, l;
    int *a_mat, *b_mat;

    MPI_Init(NULL, NULL);
    double start_time = MPI_Wtime();

    construct_matrices(&n, &m, &l, &a_mat, &b_mat);
    matrix_multiply(n, m, l, a_mat, b_mat);
    destruct_matrices(a_mat, b_mat);

    double end_time = MPI_Wtime();
    MPI_Finalize();
    printf("MPI running time: %lf Seconds\n", end_time - start_time);

    return 0;
}


int **Allocate2dInt(int rows, int cols) {
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array= (int **)malloc(rows*sizeof(int*));
    for (int i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}

void construct_matrices(int *n_ptr, int *m_ptr, int *l_ptr, int **a_mat_ptr, int **b_mat_ptr)
{
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int numWorkers = world_size-1;
    if(myRank == 0)
    {
        /*  Construct matrix    */
        cin>>*n_ptr>>*m_ptr>>*l_ptr;
        N = *n_ptr;
        M = *m_ptr;
        L = *l_ptr;
        for(int dest=1; dest<=numWorkers; dest++)
        {
            // printf("%d send %d %d %d to %d\n", myRank, N, M, L, dest);
            MPI_Send(&N, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&M, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&L, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
        }
        a_mat_ptr = Allocate2dInt(N, M);
        a = a_mat_ptr;
        b_mat_ptr = Allocate2dInt(M, L);
        b = b_mat_ptr;
        for(int row=0; row<N; row++)
        {
            for(int col=0; col<M; col++)
                cin>>a[row][col];
        }
        for(int row=0; row<M; row++)
        {
            for(int col=0; col<L; col++)
                cin>>b[row][col];
        }
    }
    else
    {
       
        MPI_Status status;
        // printf("%d waiting to recv\n", myRank);
        MPI_Recv(&N, 1, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        MPI_Recv(&M, 1, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        MPI_Recv(&L, 1, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        // printf("%d recv %d %d %d from %d\n", myRank, N, M, L, 0);
        a_mat_ptr = Allocate2dInt(N, M);
        a = a_mat_ptr;
        b_mat_ptr = Allocate2dInt(M, L);
        b = b_mat_ptr;
    }
}

void matrix_multiply(const int n, const int m, const int l, const int *a_mat, const int *b_mat)
{
    if(myRank == 0)
    {
        /*  Send data to worker */
        MPI_Status status;
        int numWorkers = world_size;
        int avgRow = N / numWorkers;
        int extraRow = N % numWorkers;
        int rows = (0 < extraRow) ? avgRow+1 : avgRow;
        int offset = 0 + rows;
        
        for (int dest=1; dest<numWorkers; dest++)
        {
            rows = (dest < extraRow) ? avgRow+1 : avgRow;  	
            MPI_Send(&offset, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&(a[offset][0]), rows*M, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            MPI_Send(&(b[0][0]), M*L, MPI_INT, dest, FROM_MASTER, MPI_COMM_WORLD);
            offset = offset + rows;
        }

        rows = (0 < extraRow) ? avgRow+1 : avgRow;
        c = Allocate2dInt(N, L);
        for (int k=0; k<L; k++)
        {
            for (int i=0; i<rows; i++)
            {
                c[i][k] = 0;
                for (int j=0; j<M; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        }

        // /* Receive results from worker tasks */
        for (int source=1; source<numWorkers; source++)
        {
            MPI_Recv(&offset, 1, MPI_INT, source, FROM_WORKER, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, FROM_WORKER, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], rows*L, MPI_INT, source, FROM_WORKER, MPI_COMM_WORLD, &status);
        }

        /* Print results */
        for (int i=0; i<N; i++)
        { 
            for (int j=0; j<L; j++)
            {
                printf("%d ", c[i][j]);
            } 
            printf("\n");
        }
    }
    else
    {
        MPI_Status status;
        int offset, rows;
        MPI_Recv(&offset, 1, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        MPI_Recv(&(a[offset][0]), rows*M, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);
        MPI_Recv(&(b[0][0]), M*L, MPI_INT, 0, FROM_MASTER, MPI_COMM_WORLD, &status);

        c = Allocate2dInt(rows, L);
        for (int k=0; k<L; k++)
        {
            for (int i=0; i<rows; i++)
            {
                c[i][k] = 0;
                for (int j=0; j<M; j++)
                    c[i][k] = c[i][k] + a[i+offset][j] * b[j][k];
            }
        }
        
        MPI_Send(&offset, 1, MPI_INT, 0, FROM_WORKER, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, FROM_WORKER, MPI_COMM_WORLD);
        MPI_Send(&c[0][0], rows*L, MPI_INT, 0, FROM_WORKER, MPI_COMM_WORLD);

    }
}

// Remember to release your allocated memory
void destruct_matrices(int *a_mat, int *b_mat)
{
    free(a[0]);
    free(a);
    free(b[0]);
    free(b);
    free(c[0]);
    free(c);
}

