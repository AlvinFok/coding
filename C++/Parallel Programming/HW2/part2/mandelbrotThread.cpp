#include <stdio.h>
#include <thread>
#include <future>
#include "CycleTimer.h"

#define rowPerTimes 30
typedef struct
{
    float x0, x1;
    float y0, y1;
    unsigned int width;
    unsigned int height;
    int maxIterations;
    int *output;
    int threadId;
    int numThreads;
} WorkerArgs;

extern void mandelbrotSerial(
    float x0, float y0, float x1, float y1,
    int width, int height,
    int startRow, int numRows,
    int maxIterations,
    int output[]);

//
// workerThreadStart --
//
// Thread entrypoint.
void workerThreadStart(WorkerArgs *const args)
{

    // clock_t begin = clock();
    // TODO FOR PP STUDENTS: Implement the body of the worker
    // thread here. Each thread should make a call to mandelbrotSerial()
    // to compute a part of the output image.  For example, in a
    // program that uses two threads, thread 0 could compute the top
    // half of the image and thread 1 could compute the bottom half.

    // int numRows = args->height / args->numThreads;
    // int startRow = args->threadId * numRows;
    int numRows = rowPerTimes;
    for(unsigned int startRow = args->threadId * numRows; startRow < args->height; startRow += rowPerTimes*args->numThreads){
        // printf("ID:%d\tstartRow:%d\t\n",args->threadId, startRow);
        mandelbrotSerial(args->x0, args->y0, args->x1, args->y1, args->width, args->height, startRow, numRows, args->maxIterations, args->output);
    }
    
    
    // clock_t end = clock();
    // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    // printf("%d %lf\n",args->threadId, elapsed_secs);
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning std::threads.
void mandelbrotThread(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    static constexpr int MAX_THREADS = 32;
    
    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    // Creates thread objects that do not yet represent a thread.
    std::thread workers[numThreads];
    WorkerArgs args[numThreads];
    int count = 0;
    for (int i = 0; i < numThreads; i++)
    {
        // TODO FOR PP STUDENTS: You may or may not wish to modify
        // the per-thread arguments here.  The code below copies the
        // same arguments for each thread
        // printf("i = %d\n",i);
        args[i].x0 = x0;
        args[i].y0 = y0;
        args[i].x1 = x1;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].numThreads = numThreads;
        args[i].output = output;

        args[i].threadId = i;
        count++;
    }
    // printf("%d\n",count);
    // Spawn the worker threads.  Note that only numThreads-1 std::threads
    // are created and the main application thread is used as a worker
    // as well.
    
    // #pragma omp parallel for num_threads(numThreads) schedule(dynamic)
    // for(int i = 0;i < height;i+=rowPerTimes){
    //     workerThreadStart(&args[i]);
    // }
    
    for (int i = 1; i < numThreads; i++)
    {
        // printf("%d\n", j+i);
        workers[i] = std::thread(workerThreadStart, &args[i]);
        // std::async(std::launch::async, workerThreadStart, &args[i]);
        printf("%d\n",workers[i].get_id());
    }

    workerThreadStart(&args[0]);

    // join worker threads
    for (int i = 1; i < numThreads; i++)
    {
        workers[i].join();
    }
    
    
}
