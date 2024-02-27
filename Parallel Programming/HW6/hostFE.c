#include <stdio.h>
#include <stdlib.h>
#include "hostFE.h"
#include "helper.h"

void hostFE(const int filterWidth, float *filter, const int imageHeight, const int imageWidth,
            float *inputImage, float *outputImage, cl_device_id *device,
            cl_context *context, cl_program *program)
{

    int filterSize = filterWidth * filterWidth;
    int imageSize = imageHeight * imageWidth;

    cl_command_queue queue = clCreateCommandQueue(*context, *device, 0, NULL);

    cl_mem d_filter = clCreateBuffer(*context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, filterSize * sizeof(float), (void *)filter, NULL);
    cl_mem d_inputImage = clCreateBuffer(*context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, imageSize * sizeof(float), (void *)inputImage, NULL);
    cl_mem d_outputImage = clCreateBuffer(*context, CL_MEM_WRITE_ONLY, imageSize * sizeof(float), NULL, NULL);

    // clEnqueueWriteBuffer(queue, d_filter, CL_TRUE, 0, filterSize, (void *)filter, 0, NULL, NULL);
    
    // clEnqueueWriteBuffer(queue, d_inputImage, CL_TRUE, 0, imageSize, (void *)inputImage, 0, NULL, NULL);
    

    cl_kernel kernel = clCreateKernel(*program , "convolution" , NULL);

    clSetKernelArg(kernel, 0, sizeof(cl_int), (void *)&filterWidth);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&d_filter);
    clSetKernelArg(kernel, 2, sizeof(cl_int), (void *)&imageHeight);
    clSetKernelArg(kernel, 3, sizeof(cl_int), (void *)&imageWidth);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&d_inputImage);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&d_outputImage);

    size_t localws[2] = {25, 25} ;
    size_t globalws[2] = {imageWidth, imageHeight};
    clEnqueueNDRangeKernel(queue, kernel, 2, 0, globalws, localws, 0, NULL, NULL);

    clEnqueueReadBuffer(queue, d_outputImage, CL_TRUE, 0, imageSize * sizeof(float), (void *) outputImage, 0, NULL, NULL);

    // clReleaseKernel(kernel);
    // clReleaseMemObject(d_filter);
    // clReleaseMemObject(d_inputImage);
    // clReleaseMemObject(d_outputImage);
    // clReleaseCommandQueue(queue);
}



    /*
    cl_int status;
    int filterSize = filterWidth * filterWidth;
    int imageSize = imageHeight * imageWidth;
    char sourceProgram = readSource("kernel.cl");
    
    cl_command_queue commandQueue = clCreateCommandQueue(*context, *device, 0, NULL);
    
    cl_mem inputImageMem = clCreateBuffer(*context, CL_MEM_READ_ONLY, imageSize * sizeof(float), NULL, NULL);
    cl_mem outputImageMem = clCreateBuffer(*context, CL_MEM_WRITE_ONLY, imageSize * sizeof(float), NULL, NULL);
    cl_mem filterMem = clCreateBuffer(*context, CL_MEM_READ_ONLY, filterSize * sizeof(float), NULL, NULL);

    clEnqueueWriteBuffer(commandQueue, inputImageMem, CL_TRUE, 0, imageSize * sizeof(float), inputImage, 0, NULL, NULL);
    clEnqueueWriteBuffer(commandQueue, filterMem, CL_TRUE, 0, filterSize * sizeof(float), filter, 0, NULL, NULL);

    cl_kernel kernel = clCreateKernel(*program, "convolution", NULL);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&inputImageMem);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&outputImageMem);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&filterMem);
    clSetKernelArg(kernel, 3, sizeof(cl_int), (void *)&imageHeight);
    clSetKernelArg(kernel, 4, sizeof(cl_int), (void *)&imageWidth);
    clSetKernelArg(kernel, 5, sizeof(cl_int), (void *)&filterWidth);

    size_t globalItemSize = imageSize;
    size_t localItemSize = 64;
    clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalItemSize, &localItemSize, 0, NULL, NULL);
    clEnqueueReadBuffer(commandQueue, outputImageMem, CL_TRUE, 0, imageSize * sizeof(float), outputImage, 0, NULL, NULL);*/




