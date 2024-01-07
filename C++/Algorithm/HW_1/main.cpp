#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <map>
#include <string>

using namespace std;


int* initializeData(int);
void printData(int*, int);
int* bubbleSort(int*, int);
int* insertionSort(int*, int);
int* selectionSort(int*, int);
int* quickSort(int*, int, int);
int* minHeapSort(int*, int);
int* buildMinHeap(int*, int);
void sortTest(int*, int);
int* quickSortWrapper(int*, int);
void toCSV(map<string, vector<double> >);

int main()
{
    srand(time(NULL));
    int DATA_SIZE = 10;
    
    int* unsortData = initializeData(DATA_SIZE);
    int* tmpData;
    sortTest(unsortData, DATA_SIZE);
    
    DATA_SIZE = 50000;
    clock_t start, finish;
    string sortTypeArray[5] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Quick Sort", "Heap Sort"};
    int* (*testFunction[5])(int*, int) = {bubbleSort, insertionSort, selectionSort,quickSortWrapper,  minHeapSort};
    map<string, vector<double> > csvData;
    for (int i = 0; i < 6; i++, DATA_SIZE += 50000)
    {
        for (int round = 0; round < 1; round++)
        {
            unsortData = initializeData(DATA_SIZE);

            for (int sortType = 0; sortType < 5; sortType++)
            {
                tmpData = initializeData(DATA_SIZE);
                
                start = clock();
                testFunction[sortType](tmpData, DATA_SIZE);
                
                finish = clock();
                double duration = double(finish - start) / CLOCKS_PER_SEC;
                printf("%d\n", DATA_SIZE);
                printf("%s:%d\n", sortTypeArray[sortType].c_str(), round + 1);
                printf("%lf\n", duration);
                string key = sortTypeArray[sortType] + "(" + to_string(DATA_SIZE) + ")";
                csvData[key].push_back(duration);
            }
        }
    }

    toCSV(csvData);
    return 0;
}
void sortTest(int* unsortData, int size)
{
    int* tmpData = unsortData;
    //print unsort data
    printf("%-15s:", "unsort data");
    printData(unsortData, size);
    //print bubble sort
    tmpData = bubbleSort(tmpData, size);
    printf("%-15s:", "bubble sort");
    printData(tmpData, size);
    //************************
    //print insertion sort
    tmpData = unsortData;
    tmpData = insertionSort(tmpData, size);
    printf("%-15s:", "insertion sort");
    printData(tmpData, size);
    //************************
    //print selection sort
    tmpData = unsortData;
    tmpData = selectionSort(tmpData, size);
    printf("%-15s:", "selection sort");
    printData(tmpData, size);
    //************************
    //print quick sort
    tmpData = unsortData;
    tmpData = quickSortWrapper(tmpData, size);
    printf("%-15s:", "quick sort");
    printData(tmpData, size);
    //************************
    //print min heap sort
    tmpData = unsortData;
    // tmpData.insert(tmpData.begin(), 0);
    tmpData = minHeapSort(tmpData, size);
    printf("%-15s:", "min heap sort");
    printData(tmpData, size);
}

void printData(int* data, int size)
{
    
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int* initializeData(int size)
{
    int* data = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        data[i] =rand() % size;
    }
    return data;
}

int* bubbleSort(int* data, int size)
{
    
    for (int i = size - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (data[j] > data[j + 1])
            {
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
    return data;
}

int* insertionSort(int* data, int size)
{
    
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (data[j] < data[j - 1])
            {
                int tmp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = tmp;
            }
        }
    }
    return data;
}

int* selectionSort(int* data, int size)
{
    
    for (int i = 0; i < size; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            int tmp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = tmp;
        }
    }
    return data;
}

int* quickSort(int* data, int left, int right)
{
    if(left < right){
        int i=left - 1, piovt = data[right], tmp;
        for(int j=left; j<right; j++){
            if(data[j] < piovt){
                i++;
                tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
            
        }
        i++;
        tmp = data[i];
        data[i] = data[right];
        data[right] = tmp;
        quickSort(data, left, i - 1);  // 對左子串列進行快速排序
        quickSort(data, i+1, right);   // 對右子串列進行快速排序
    }
    return data;
}


void minHeapify(int* data, int root, int size)
{
    
        int left = 2 * root, right = 2 * root + 1, min = root;
        if (left < size && data[left] < data[root])
        {
            min = left;
        }
        if (right < size && data[right] < data[min])
        {
            min = right;
        }
        if (min != root)
        {
            int tmp = data[min];
            data[min] = data[root];
            data[root] = tmp;
            minHeapify(data, min, size);
        }
}

int* buildMinHeap(int* data, int size)
{
    
    for (int i = size / 2; i >= 1; i--)
    {
        minHeapify(data, i, size);
    }
    return data;
}

int* minHeapSort(int* data, int size)
{
    data = buildMinHeap(data, size);
    int* sorted = (int*)malloc(size*sizeof(int));
    int j = 0;
    for (int i = size - 1; i >= 1; i--)
    {
        sorted[j++] = data[1];
        data[1] = data[i];
        minHeapify(data, 1, i);
    }
    return sorted;
}

int* quickSortWrapper(int* data, int size)
{
    return quickSort(data, 0, size - 1);
}

void toCSV(map<string, vector<double> > data)
{
    fstream file;
    file.open("results.csv", ios::out);
    map<string, vector<double> >::iterator it = data.begin();
    while (it != data.end())
    {
        string key = it->first;
        vector<double> value = it->second;
        file << key;
        for (int i = 0; i < value.size(); i++)
        {
            file << "," << value[i];
        }
        file << endl;
        it++;
    }
    file.close();
}