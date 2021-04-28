#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    int fd[2];

    if(pipe(fd) != 0) {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0) {
        //stdin(0) -> teclado
        //stdout(1) -> ecra
        //fd[0] -> leitura pipe
        //fd[1] -> escrita pipe
        close(fd[1]);   

        //stdin(0) -> teclado
        //stdout(1) -> ecra
        //fd[0] -> leitura pipe
        dup2(fd[0], 0);

        //stdin(0) -> leitura pipe
        //stdout(1) -> ecra
        //fd[0] -> leitura pipe
        close(fd[0]);    

        //stdin(0) -> leitura pipe
        //stdout(1) -> ecra

        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }

    close(fd[0]);  

    if (fork() == 0) {
        //stdin(0) -> teclado
        //stdout(1) -> ecra
        //fd[1] -> escrita pipe
        dup2(fd[1], 1);
        close(fd[1]);

        //stdin(0) -> teclado
        //stdout(1) -> escrita pipe

        execlp("ls", "ls", "/etc", NULL);
        _exit(1);
    }

    //stdin(0) -> teclado
    //stdout(1) -> ecra
    //fd[1] -> escrita pipe
    close(fd[1]);
    
    wait(NULL);
    wait(NULL);

    return 0;
}