#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include "messages.h"

int main()
{
    descrimsg msg;             /* message */
    int msgid;                      /* Identificateur de la file de messages */
    int i=0;

    /*
    * Création de la file de messages
    */
    msgid = open_queue( CLE_MESS );

    for (i=0; i<10; ++i)
    {
        read_message(msgid, MON_TYP_CLI, &msg );

        printf("Server %d received message from client %d\n", getpid(), msg.pid);
        printf("Message received: %s\n", msg.mtext) ;

        strcpy(msg.mtext, "Server's answer") ; /* Champ mtext rempli */
        msg.pid = getpid();
        msg.mtype = MON_TYP_SER; /* valeur arbitraire */
        printf("Server: sending answer :%s\n",msg.mtext) ;
        send_message(msgid, &msg);
    }
}
