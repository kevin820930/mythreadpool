#ifndef MYTHREADPOOL_H
#define MYTHREADPOOL_H

#define MAX_THREADS 32
#define MAX_QUEUE 65536
void *hello(int *num);
typedef struct threadpool_t threadpool;
/*typedef struct threadpool{
  pthread_mutex_t lock;
  pthread_t *threads;
  int thread_count;
  int queue_size;
  int head;
  int tail;
  int count;
}threadpool_t;
*/
typedef struct tasking {
    void (*function)(void *);
    void *argument;
} task;

threadpool *threadpool_create(int thread_count, int queue_size);
void *thread(threadpool *threadpool);
void *taskover(threadpool *pool);
#endif
