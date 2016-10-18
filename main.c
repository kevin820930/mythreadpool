#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#include "mythreadpool.h"

void *try(int *n){
printf("---%d---\n",(*n)*(*n));

}

int main()
{

    int count=0;
    int n=0;
    int addoroff=0;
    threadpool *pool=threadpool_create(MAX_THREADS,MAX_QUEUE);

    while(addoroff==0) {

        printf("what do you want to do 1 for add 2 for exit\n");
        scanf("%d", &addoroff);

        if(addoroff==1) {
            for(n=0; n<1000; n++) {
                int *num=(int *) malloc(sizeof(int));
                *num=n;
                //for(count=0;count<1000;count++);
                task_add(pool,try,num);
            }
            addoroff=0;
        }

        if(addoroff==2) {
            taskover(pool);
        }

    }

}
/*
int main(){

int count=0;
int *num=(int *) malloc(sizeof(int)*1000);
int n;
threadpool *pool=threadpool_create(MAX_THREADS,MAX_QUEUE);
for(count=0;count<5000000;count++);
for(n=0;n<1000;n++){
    num[n]=n;
    printf("add ? %d \n",num[n]);
    for(count=0;count<100000;count++);
    task_add(pool,hello,&num[n]);
}

}*/
