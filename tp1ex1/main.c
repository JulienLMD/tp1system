
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_fpe(int sig)
{
    printf("On a notre signale !\n");
    printf("\n");
}

//
int main(int argc, char *argv[], char *envp[])
{
    signal(SIGPIPE, sig_fpe);
    int tube[2];
    if (-1) {
        printf("bonjour\n");
    }
    if (0) {
        printf("non bonjour\n");
    }
    printf("bonjour\n");
    pipe(tube);
    close(tube[0]);
    write(tube[1],"AB",2);
    if (-1) {
        perror("erreurdsrdd");
    }
    exit(0);
}
