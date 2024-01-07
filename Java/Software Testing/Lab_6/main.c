#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int global_a[3]={0};
char* x;

void heap(){
    int* a = malloc(sizeof(int)*3);
    a[3] = 0;
}

void stack() {
    static int a[3]={0};
    a[3] = 0;
}

void global(){
    global_a[3] = 0;
}

void useFree(){
    int* a = malloc(sizeof(int)*3);
    free(a);
    a[2] = 1;
}

void useReturn() {
    char stack_buffer[42];
    x = &stack_buffer[13];
}

void redzone(){
    int a[8] = {0};
    int b[8] = {0};
    a[16] = 0;
}

int main(){
    // heap();
    // stack();
    // global();
    // useFree();
    // useReturn();
    // *x = 42;
    redzone();
    return 0;
}