//
//  main.c
//  tp1ex2
//
//  Created by Matthieu on 11/7/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>

void * additionneur(void *);

#define nbt 2
pthread_t tid[nbt];
int nombre = 0;
pthread_mutex_t mutex;

int main( int argc, char *argv[] ) {
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i=0; i<nbt; i++) {
        pthread_create(&tid[i], NULL, additionneur, NULL);
    }
    for ( i = 0; i < nbt; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("main signale que les %d threads ont terminé\n", i);
    printf("Je suis main ! nombre=%d\n", nombre);
}

void * additionneur(void * parm) {
    int i;
    printf("Je suis un nouveau thread !\n");
    
    pthread_mutex_lock(&mutex);
    for(i=0;i<200000;i++) {
        nombre++;
    }
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(0);
}
