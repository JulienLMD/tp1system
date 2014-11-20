//
//  main.c
//  tp1ex4
//
//  Created by Matthieu on 11/7/14.
//  Copyright (c) 2014 Matthieu. All rights reserved.
//

//#include <stdio.h>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    printf("Hello, World!\n");
//    system("echo Hello");
////    echo "Message Body" | /usr/bin/mail -s "Message Title" matthieudelaro@gmail.com
//    return 0;
//}

///
/* Envoi d'un mail ‡ un utilisateur via un tube */
/*** Remplacer les points par les instructions ou les parametres manquants ***/

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
    pipe(desctube);
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
        dup2(desctube[1], 1); // redirect stdout
        
        /*
         * Pour voir la sortie sur l'ecran, on ferme le tube en ecriture.
         */
        close(desctube[1]);
        
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
        close(desctube[0]);
        fp = fdopen(desctube[1], "w");
        //    fp = fdopen(...,... );
        fprintf(fp, "C'est le message que vous attendez, cher utilisateur.\n");
        fclose(fp);
        
        /*
         * Le pere attend la terminaison du fils
         */
        int status;
        wait(&status);
        exit(0);
    }

}

//Using pipes as file streams, fdopen()
//
//#include <stdio.h>
//#include <unistd.h>
//#include <sys/types.h>
//
//#define MAXLINE         512
//
//int main(void) {
//    char line[MAXLINE];
//    FILE *fpin  = {0};
//    FILE *fpout = {0};
//    pid_t child = -1;
//    int fd[2] = {0};
//    int i = 0;
//    
//    pipe(fd);
//    
//    if((child = fork()) == -1) {
//        perror("fork");
//        return 1;
//    }
//    
//    if(child == 0) {
//        close(fd[0]);
//        
//        fpout = fdopen(fd[1], "w");
//        if(fpout == NULL) {
//            fprintf(stderr, "Error - fdopen(child)\n");
//            return 1;
//        }
//        
//        for(i = 0; i < 10; i++)
//            fprintf(fpout, "%s\n", "jeronimooo...");
//        
//        fclose(fpout);
//        return 0;
//    } else {
//        close(fd[1]);
//        
//        fpin = fdopen(fd[0], "r");
//        if(fpin == NULL) {
//            fprintf(stderr, "Error - fdopen(parent)\n");
//            return 1;
//        }
//        
//        while(fgets(line, MAXLINE, fpin) != NULL)
//            printf("%d: %s", i++, line);
//        
//        fclose(fpin);
//    }
//    
//    return 0;
//}


