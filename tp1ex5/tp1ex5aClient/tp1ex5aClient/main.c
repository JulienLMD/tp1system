//
//  main.c
//  tp1ex5aClient
//
//  Created by Matthieu on 12/4/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "../../wrapperMsg.h"

#define  CLE_MESS     	131      /* La clé associée à la file de messages */

#define  LONG_MESS 	512  	/* La longueur du message */

#define  LONG_MESS_MAX 	600    	/* la longueur max du message */

#define  MON_TYP_CLI 10       	/* Le type de messages adressés au client  */
#define  MON_TYP_SER 20      	/* Le type des messages adressés au serveur */

struct decrimsg     {
    long     mtype;
    int      pid;
    char     mtext[LONG_MESS];
};

int main()
{
    struct decrimsg msg, received;                         /* message */
    int msgid;                                  /* identificateur de la file */
    char *message_t10 = "Ici l'EFREI: bonjour L3a" ;   /* texte du message */
    int buf_length = sizeof(long) + sizeof(int) + LONG_MESS * sizeof(char);
    
    /*
     * Récupération de l'identificateur de la file de messages
     */
    msgid = msggetW(CLE_MESS, IPC_CREAT | 0666);
    
    /*
     * Envoi d'un message (commencer par remplir les champs de msg)
     */
    strcpy(msg.mtext, message_t10) ; /* Champ mtext rempli */
    printf("client: envoi du message:%s\n",msg.mtext) ;
    //msgsnd
    msgsnd(msgid, &msg, buf_length, IPC_NOWAIT);
    
//    ...
    /*
     * Réception d'un message
     */
    printf("client: attente de message\n") ;
    if (msgrcv(msgid, &received, buf_length, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    } else {
        printf("client: recu:%s\n",received.mtext) ;
    }
    //msgrcv
    
//    ...
    
    printf("processus client = %d reçoit un message du serveur %d\n", getpid(), msg.pid);
    return EXIT_SUCCESS;
}

//tube
//tube nommé
//sémaphores
//mémoire partagée
//=> queue/file de messages
//
//msgget : créer un canal de communication de message

