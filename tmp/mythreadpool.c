#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//#include "mythreadpool.h"
int *hello(int a){
printf("test %d\n",a);
}

threadpool_t *threadpool_create(int thread_count, int queue_size){

   threadpool_t *pool=(threadpool_t *) malloc(sizeof(threadpool_t));
   pool->queue_size=queue_size;
   pool->thread_count=thread_count;

   for(i = 0; i < thread_count; i++) {
        if(pthread_create(&(pool->threads[i]), NULL,threadpool_thread, (void*)pool) != 0) {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }
    
    return pool;
}
