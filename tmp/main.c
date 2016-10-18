#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#include "mythreadpool.h"

int main(){
task *t1=(task *) malloc(sizeof(task));
hello(100);
(t1+0)->function=(void *)hello(400);
(t1+0)->function;

threadpool_create(MAX_THREADS,MAX_QUEUE);
}

