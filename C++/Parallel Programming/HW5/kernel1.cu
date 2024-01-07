#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void mandelKernel(float x0, float y0, float dx, float dy, int width, int* img, int maxIterations) {
    // To avoid error caused by the floating number, use the following pseudo code
    //
    // float x = lowerX + thisX * stepX;
    // float y = lowerY + thisY * stepY;
    int thisX = blockIdx.x * blockDim.x + threadIdx.x;
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
        

    int index = (thisY * width + thisX);
    img[index] = i;
       
}

// Host front-end function that allocates the memory and launches the GPU kernel
void hostFE (float upperX, float upperY, float lowerX, float lowerY, int* img, int resX, int resY, int maxIterations)
{
    float stepX = (upperX - lowerX) / resX;
    float stepY = (upperY - lowerY) / resY;
    int *h_img, *d_img;
    h_img = (int *)malloc(resX * resY * sizeof(int));
    cudaMalloc((void**) &d_img, resX * resY * sizeof(int));
    dim3 threadPerBlock(16, 16);
    dim3 numBlock(resX / threadPerBlock.x, resY / threadPerBlock.y);
    mandelKernel<<<numBlock, threadPerBlock >>>(lowerX, lowerY, stepX, stepY, resX, d_img, maxIterations);
    cudaMemcpy(h_img, d_img, resX * resY * sizeof(int), cudaMemcpyDeviceToHost);
    memcpy(img, h_img, resX * resY * sizeof(int));
    cudaFree(d_img);
    free(h_img);
}
