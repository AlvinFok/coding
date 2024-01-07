__kernel void convolution(int filterWidth, __constant float *filter, int imageHeight, int imageWidth, const __global float *inputImage, __global float *outputImage) 
{
   // Iterate over the rows of the source image
    int halffilterSize = filterWidth / 2;
    float sum = 0.0f;
    int i, j, k, l;

    i = get_global_id(1);
    j = get_global_id(0);
    
    sum = 0; // Reset sum for new source pixel
    // Apply the filter to the neighborhood
    for (k = -halffilterSize; k <= halffilterSize; k++)
    {
        for (l = -halffilterSize; l <= halffilterSize; l++)
        {
            if(filter[(k + halffilterSize) * filterWidth + l + halffilterSize] != 0)
            {
                if (i + k >= 0 && i + k < imageHeight &&
                    j + l >= 0 && j + l < imageWidth)
                {
                    sum += inputImage[(i + k) * imageWidth + j + l] *
                            filter[(k + halffilterSize) * filterWidth +
                                    l + halffilterSize];
                }
            }
        }
    }
    outputImage[i * imageWidth + j] = sum;
}
