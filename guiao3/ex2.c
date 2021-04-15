#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]) {

    printf("Antes\n");
    int status;
    
    if (fork() == 0) {

        execl("/bin/ls","ls","-l", NULL); //se isto for executado com sucesso nada para a frente disto dentro do filho é executado

        perror("exec");

        printf("Depois dentro do filho\n");

        _exit(1);

    }
    
    wait(&status);
    
    printf("Main\n");

    return 0;
}
