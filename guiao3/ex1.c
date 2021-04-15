#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>


int main (int argc, char * argv[]) {

    printf("Antes\n");

    //execl("/bin/ls","ls","-l", NULL);
    //execlp("ls","ls","-l", NULL); //se isto for executado com sucesso nada para a frente disto é executado

    char * argv_exec[] = {
        "/bin/ls",
        "-l",
        NULL
    };

    execv("/bin/ls", argv_exec);


    perror("exec");

    printf("Depois\n");

    return 0;
}
