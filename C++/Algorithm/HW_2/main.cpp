#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
};

bool compare(const Point &a, const Point &b)
{
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

double cross(Point o, Point a, Point b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int main()
{
    srand(time(NULL));
    int size;
    printf("Input Number Of Points:");
    cin >> size;
    Point p[size], vertex[size + 1];
    //initialize data
    for (int i = 0; i < size; i++)
    {
        p[i].x = rand() % size / 2;
        p[i].y = rand() % size / 2;
    }

    //sort all points by x value
    sort(p, p + size, compare);

    int numOfVertex = 0;

    //find lower convex hull
    for(int i = 0; i < size; i++){
        while(numOfVertex >=2 && cross(vertex[numOfVertex-2], vertex[numOfVertex-1], p[i]) <= 0){
            numOfVertex--;
        }
        vertex[numOfVertex++] = p[i];
    }

    //find upper convex hull
    for (int i = size - 2, t=numOfVertex+1; i>=0; i--){
        while(numOfVertex>=t && cross(vertex[numOfVertex-2], vertex[numOfVertex-1], p[i]) <= 0){
            numOfVertex--;
        }
        vertex[numOfVertex++] = p[i];
    }
    numOfVertex--;

    return 0;
}