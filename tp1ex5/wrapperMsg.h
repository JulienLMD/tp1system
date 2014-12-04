//
//  wrapperMsg.h
//  tp1ex5aClient
//
//  Created by Matthieu on 12/4/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//

#ifndef tp1ex5aClient_wrapperMsg_h
#define tp1ex5aClient_wrapperMsg_h

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//struct decrimsg     {
//    long     mtype;
//    int      pid;
//    char     mtext[LONG_MESS];
//};

int msggetW(key_t, int);
//int msgsndW(int msqid, const void *msgp, size_t msgsz, int msgflg);


int msggetW(key_t key, int ipc) {
    int msgid;
    msgid = msgget(key, ipc);
    if (msgid < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return msgid;
}

//int msgsndW(int msqid, const void *msgp, size_t msgsz, int msgflg) {
//    int result = msgsnd(msqid, &msgp, msgsz, msgflg);
//    if (result == -1) {
//        printf ("%d, %d, %s, %d\n", msqid, msgp.mtext, msgp.mtext, msgsz);
//        perror("msgsnd");
//        exit(1);
//    }
//}

#endif
