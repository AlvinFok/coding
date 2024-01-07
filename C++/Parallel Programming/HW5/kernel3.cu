#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void mandelKernel(float x0, float y0, float dx, float dy, int width, int* img, int maxIterations, int pitch, int pixelsPerThread) {
    // To avoid error caused by the floating number, use the following pseudo code
    //
    // float x = lowerX + thisX * stepX;
    // float y = lowerY + thisY * stepY;
    for(int j = 0; j < pixelsPerThread; j++){

    
        int thisX = (blockIdx.x * blockDim.x + threadIdx.x) * pixelsPerThread + j;
        int thisY = blockIdx.y * blockDim.y + threadIdx.y;
        float x = x0 + thisX * dx;
        float y = y0 + thisY * dy;
        float tmpX = x, tmpY = y;
        int i;
        for (i = 0; i < maxIterations; ++i)
        {

            if (tmpX * tmpX + tmpY * tmpY > 4.f)
            break;

            float new_x = tmpX * tmpX - tmpY * tmpY;
            float new_y = 2.f * tmpX * tmpY;
            tmpX = x + new_x;
            tmpY = y + new_y;
        }
            

        int* row =  (int*)((char*)img + thisY * pitch);
        row[thisX] = i;
    }
       
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;
    int *d_img, *h_img;
    int pixelsPerThread = 10;
    size_t pitch;
    cudaHostAlloc((void **)&h_img, resX * resY * sizeof(int), cudaHostAllocDefault);
    cudaMallocPitch((void**) &d_img, &pitch, resX * sizeof(int), resY);
    dim3 threadPerBlock(16, 16);
    dim3 numBlock(resX / (threadPerBlock.x *pixelsPerThread), resY / threadPerBlock.y);
    mandelKernel<<<numBlock, threadPerBlock >>>(lowerX, lowerY, stepX, stepY, resX, d_img, maxIterations, pitch, pixelsPerThread);
    cudaMemcpy2D(h_img, resX * sizeof(int), d_img, pitch, resX * sizeof(int), resY, cudaMemcpyDeviceToHost);
    memcpy(img, h_img, resX * resY * sizeof(int));
    cudaFreeHost(h_img);
    cudaFree(d_img);
}
