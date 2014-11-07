//
//  main.c
//  tp1ex3
//
//  Created by Matthieu on 11/7/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS  2
#define COUNT_LIMIT 4

int     count = 0;
int     goOn = 1;
int     thread_ids[2] = {0,1};
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void *t)
{
    long my_id = (long)t;
    
    while (goOn) {
        pthread_mutex_lock(&count_mutex);
        count++;
        
        /*
         Check the value of count and signal waiting thread when condition is
         reached.  Note that this occurs while mutex is locked.
         */
        if (count == COUNT_LIMIT) {
            pthread_cond_signal(&count_threshold_cv);
            printf("inc_count(): thread %ld, count = %d  Threshold reached.\n",
                   my_id, count);
        }
        printf("inc_count(): thread %ld, count = %d, unlocking mutex\n",
               my_id, count);
        pthread_mutex_unlock(&count_mutex);
        
        /* Do some "work" so threads can alternate on mutex lock */
        sleep(1);
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    int i;
    long t1=1, t2=2;
    pthread_t threads[2];
    pthread_attr_t attr;
    
    /* Initialize mutex and condition variable objects */
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);
    
    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, inc_count, (void *)t1);
    pthread_create(&threads[1], &attr, inc_count, (void *)t2);
    
    pthread_mutex_lock(&count_mutex);
    while (count<COUNT_LIMIT) {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): main thread Condition signal received.\n");
        goOn = 0;
        printf("watch_count(): main thread count now = %d.\n", count);
    }
    pthread_mutex_unlock(&count_mutex);
    
    /* Wait for all threads to complete */
    for (i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);
    
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL);
    
}