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
        printf("found user : %s", utilisateur);
    }
    
    /*
     * Creation du tube et appel de fork().
     */
    pipe(desctube);
    
    //    ...
    
    /* Ici le fils !
     * Envoi par le fils ‡ l'utilisateur du message contenu dans le tube
     */
    if (idp == 0) {
        /*
         * Redirection de l'entree standard vers le tube
         */
//        ...
//        ...
//        ...
        
        /*
         * Pour voir la sortie sur l'ecran, on ferme le tube en ecriture.
         */
//        ...
        /*
         * Envoi du mail
         */
        execl("/usr/bin/mail", "mail", utilisateur, 0);//working on mac os
        perror("Exec a echoue !");
        exit(1);
    } else {
        
        /* Ici le pere !
         * Le pere ecrit le message dans le tube
         */
        printf("Surveillez votre BAL, si tout se passe bien, un message vous sera envoye \n");
        close(desctube[0]);
        //    fp = fdopen(...,... );
        fprintf(fp, "C'est le message que vous attendez, cher utilisateur.\n");
        fclose(fp);
        
        /*
         * Le pere attend la terminaison du fils
         */
        //...
        exit(0);
    }

}

