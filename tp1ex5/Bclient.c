#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include "messages.h"


int main()
{
    descrimsg msg;                         /* message */
    int msgid, msgid2;                                  /* identificateur de la file */
    char *message_t10 = "Efrei talking : Hi guys !" ;   /* texte du message */

    msgid = open_queue( CLE_MESS );
	msgid2 = open_queue( CLE_MESS_2 );

    strcpy(msg.mtext,message_t10) ; /* Champ mtext rempli */
    msg.pid = getpid();
	msg.mtype = MON_TYP_CLI; /* valeur arbitraire */
    printf("Client:sending message:%s\n",msg.mtext) ;

	send_message(msgid, &msg);

	printf("Client:waiting for a message\n") ;
	read_message(msgid2, MON_TYP_SER, &msg );

    printf("Client %d received message fron server %d\nText: %s\n", getpid(), msg.pid, msg.mtext);

	return EXIT_SUCCESS;
}
