#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

int main()
{
    int *num=(int *) malloc(sizeof(int));;
    *num=0;
    for(; (*num)<1000; (*num)++) {
        printf("--%d--\n",(*num));
    }
    return 0;
}

