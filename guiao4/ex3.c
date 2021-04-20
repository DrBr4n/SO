#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char * argv[]) {

    int inputFd = open("intput.txt", O_RDONLY);

    int outputFd = open("saida.txt", O_CREAT | O_TRUNC | O_RDONLY, 0644);

    int errorFd = open("erros.txt", O_CREAT | O_TRUNC | O_RDONLY, 0644);

    dup2(inputFd, 0);
    close(inputFd);

    dup2(outputFd, 1);
    close(outputFd);

    dup2(errorFd, 2);
    close(errorFd);

    if (fork() == 0) {
        
        execlp("wc", "wc", NULL);

        printf("smth went r");
        
        _exit(1);
    }
    
    wait(NULL);

    return 0;
}