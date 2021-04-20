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

    char c;

    while (read(0, &c, 1) > 0) {
        write(1, &c, 1);
        write(2, &c, 1);
    }

    //if (fork() == 0) {
    //    sleep(30);
    //    //execl("~/Documents/SO/guiao1/readln", "rdln", argv, NULL);
    //
    //    printf("fs");
    //    _exit(0);
    //}

    //wait(NULL); 

    //sleep(60);


    return 0;
}