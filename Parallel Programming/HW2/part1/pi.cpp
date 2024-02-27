#include<iostream>
#include<cstdlib>
#include<ctime>
#include<pthread.h>
#include<random>


long thread_Count;
long long total = 0, total_In=0;
double pi = 0;

pthread_mutex_t mutex;


void* pi_cal(void* rank){
    long long index = total / thread_Count;
    long long start = (long)rank*index;
    long long end = start + index;
    // printf("%d\n",end);
    long long total_In_thread = 0;
    double x, y;
    unsigned int seed = (long)rank;
    // struct drand48_data randBuffer;
    // srand48_r(seed, &randBuffer);
    
    for(long long i = start; i < end; i++){
        x = (double)rand_r(&seed)/RAND_MAX;
        y = (double)rand_r(&seed)/RAND_MAX;
        // drand48_r(&randBuffer, &x);
        // seed++;
        // drand48_r(&randBuffer, &y);
        // seed++;
        if(x*x + y*y <= 1.0){
            total_In_thread++;
        }
    }

    pthread_mutex_lock(&mutex);
    total_In += total_In_thread;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char const *argv[])
{
    long thread; /* Use long in case of a 64-bit system */ 
    pthread_t* thread_handles;
    thread_Count = strtol(argv[1], NULL, 10);
    total = strtoll(argv[2], NULL, 10);
    
    thread_handles = (pthread_t*) malloc (thread_Count*sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    for (thread = 0; thread < thread_Count; thread++)
        pthread_create(&thread_handles[thread], NULL, pi_cal, (void *)thread);

    for (thread = 0; thread < thread_Count; thread++) 
        pthread_join(thread_handles[thread], NULL);

    // printf("%lld\n", total_In);
    pthread_mutex_destroy(&mutex);
    
    std::cout<<4*((double)total_In/total)<<std::endl;
    return 0;
}
