
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_fpe(int sig)
{
    printf("On a notre signale !\n");
    printf("\n");
}


int main(int argc, char *argv[], char *envp[])
{
    signal(SIGPIPE, sig_fpe);
    int tube[2];
    printf("bonjour\n");
    pipe(tube);
    close(tube[0]);
    if (write(tube[1],"AB",2) == -1) {
        perror("erreurdsrdd");
    }
    exit(0);
}
