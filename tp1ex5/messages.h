#ifndef MESSAGES
#define MESSAGES

#define  CLE_MESS       131     /* La clé associée à la file */
#define  CLE_MESS_2       132     /* La clé associée à la file : envoi de serveur vers le client */

#define  LONG_MESS  512     /* La longueur du message */

#define  LONG_MESS_MAX 600      /* La longueur max du message  */

#define  MON_TYP_CLI    10      /* Le type de messages adressés au client  */
#define  MON_TYP_SER    20      /* Le type de messages adressés au serveur */

#define MSG_R   400         /* Lecture pour le propriétaire */
#define MSG_W   200         /* Ecriture pour le propriétaire */


typedef struct decrimsg_t {
    long     mtype;
    int      pid;
    char     mtext[LONG_MESS];
} descrimsg;


/**
 * Opens a message file
 */
int open_queue( key_t keyval )
{
    int qid = msgget( keyval, IPC_CREAT | 0660 );

    if(qid == -1)
    {
        perror("Error while opening message file.");
    }

    return qid;
}

/**
 * Writes a message in file qid
 */
int send_message( int qid, descrimsg *msg )
{
    int result = msgsnd( qid, msg, LONG_MESS, 0);

    if(result == -1)
    {
        perror("Error while sending message.");
    }

    return result;
}

/**
 * Reads a message in file qid
 */
int read_message( int qid, long type, descrimsg *msg )
{
    int result = msgrcv( qid, msg, LONG_MESS, type,  0);

    if(result == -1)
    {
        perror("Error while reading message.");
    }

    return result;
}


#endif
