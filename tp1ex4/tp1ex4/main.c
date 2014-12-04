//
//  main.c
//  tp1ex4
//
//  Created by Matthieu on 11/7/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    FILE *fp;
    int idp, desctube[2];
    char *utilisateur, *getlogin();
    
    /*
     * Trouver l'utilisateur loge
     */
    if ((utilisateur = getlogin()) == NULL) {
        fprintf(stderr, "Pas d'utilisateur loge ?\n");
        exit(1);
    } else {
        printf("found user : %s\n", utilisateur);
    }
    
    /*
     * Creation du tube et appel de fork().
     */
    if (pipe(desctube))
    {
        fprintf (stderr, "Pipe failed.\n");
        return EXIT_FAILURE;
    }
    
    idp = fork();
    if (idp == -1) {
        fprintf(stderr, "Erreur avec fork()\n");
        exit(1);
    }
    /* Ici le fils !
     * Envoi par le fils ‡ l'utilisateur du message contenu dans le tube
     */
    else if (idp == 0) {
        
        /*
         * Redirection de l'entree standard vers le tube
         */
        if(close(0) == -1)
        {
            fprintf (stderr, "close(0) failed.\n");
            return EXIT_FAILURE;
        }
        if (dup(desctube[0]) < 0) // redirect stdout
        {
            fprintf (stderr, "Dup failed.\n");
            return EXIT_FAILURE;
        }
        if(close(desctube[0]) == -1)
        {
            fprintf (stderr, "close(desctube[0]) failed.\n");
            return EXIT_FAILURE;
        }
        
        /*
         * Pour voir la sortie sur l'ecran, on ferme le tube en ecriture.
         */
        if(close(desctube[1]) == -1)
        {
            fprintf (stderr, "close(desctube[1]) failed.\n");
            return EXIT_FAILURE;
        }
        
        /*
         * Envoi du mail
         */
        execl("/usr/bin/mail", "mail", utilisateur, 0);//working on mac os
        perror("Exec a echoue !\n");
        exit(1);
    } else {
        
        /* Ici le pere !
         * Le pere ecrit le message dans le tube
         */
        printf("Surveillez votre BAL, si tout se passe bien, un message vous sera envoye \n");
        if(close(desctube[0]) == -1)
        {
            fprintf (stderr, "close(desctube[0]) failed.\n");
            return EXIT_FAILURE;
        }
        fp = fdopen(desctube[1], "w");
        if (fp == NULL) {
            fprintf (stderr, "fdopen(desctube[1], \"w\") failed.\n");
            return EXIT_FAILURE;
        } else {
            fprintf(fp, "C'est le message que vous attendez, cher utilisateur.\n");
        }
        fclose(fp);
        
        /*
         * Le pere attend la terminaison du fils
         */
        int status;
        wait(&status);
        exit(0);
    }

}


