#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "mythreadpool.h"
int a=0;
struct threadpool_t {
    pthread_mutex_t lock;
    pthread_cond_t wakeup;
    pthread_t *threads;
    task *queue;
    int thread_count;
    int queue_size;
    int tasks_out;
    int tasks_in;
    int count;
    int idlethread;
    int shutdown;
};
// hello function is for test
void *hello(int *num)
{
    int a=0;
    printf("%lu kill %d  \n",pthread_self(),*num);
    for(a=0; a<33333333; a++);
}

threadpool *threadpool_create(int thread_count, int queue_size)
{

    threadpool *pool=(threadpool *) malloc(sizeof(threadpool));
    pool->queue=(task *) malloc(sizeof(task)*MAX_QUEUE);
    pool->queue_size=queue_size;
    pool->thread_count=thread_count;
    pool->threads=(pthread_t *) malloc(sizeof(pthread_t)*MAX_THREADS);
    pool->count=0;
    pool->shutdown=0;
    pool->idlethread=0;
    pool->tasks_in=0;
    pool->tasks_out=0;
    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->wakeup), NULL);

    int i,x;
    for(i = 0; i < thread_count; i++) {
        pthread_create(pool->threads+i, NULL,(void *)thread,pool);
        //if(x==0)
        //printf("\ncreate pthread %d\n",i);
        //pthread_join(pool->threads[i],NULL);
        pool->thread_count++;
    }
    /*for(i = 0; i < thread_count; i++) {
    pthread_join(pool->threads[i],NULL);
     }*/
    return pool;
}

void *thread(threadpool *pool)
{
    printf("create pthread %lu\n",pthread_self());

    task tasking;//the task doing now
    while(1) {
        pthread_mutex_lock(&(pool->lock));
        printf("thread:%lu lock when count,idle=%d,%d\n",pthread_self(),pool->count,pool->idlethread);

        while(pool->count==0 ) {
            (pool->idlethread)++;
            pthread_cond_wait(&(pool->wakeup), &(pool->lock));
            (pool->idlethread)--;
            printf("%lu begin work count= %d \n",pthread_self(),pool->count);

        }
        tasking.function = pool->queue[pool->tasks_out].function;
        tasking.argument = pool->queue[pool->tasks_out].argument;
        (pool->count)--;
        if((pool->tasks_out)==59999)
            pool->tasks_out = 0;
        else
            (pool->tasks_out)++;
        //pthread_mutex_unlock(&(pool->lock));
        printf("%lu unlock \n",pthread_self());
        pthread_mutex_unlock(&(pool->lock));

        (*(tasking.function))((int *)tasking.argument);

    }
}

void *task_add(threadpool *pool, void (*function)(void *),void *argument)
{

    pthread_mutex_lock(&(pool->lock));
    printf("have add %d\n",*(int *)argument);
    if(pool->count==60000) {
        printf("the task quene is full \n");
    } else {
        pool->queue[pool->tasks_in].function=function;
        pool->queue[pool->tasks_in].argument=argument;
        if(pthread_cond_signal(&(pool->wakeup)) != 0) {
            printf("add can't wakeup\n");
        }

        if(pool->tasks_in==59999)
            pool->tasks_in=0;
        else
            (pool->tasks_in)++;
        (pool->count)++;
    }

    if(pthread_mutex_unlock(&(pool->lock)) != 0) {
        printf("add unlock failed\n");
    }

}

void *taskover(threadpool *pool)
{
    while(pool->idlethread!=32 || pool->count !=0);
    printf("code over, idle thread=%d\n",pool->idlethread);

    //for(count=0;count<10000000;count++);
}
