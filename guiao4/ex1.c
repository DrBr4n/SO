#include <unistd.h>
#include <fcntl.h>


int main (int argc, char * argv[]) {

    int inputFd = open("/etc/passwd", O_RDONLY);

    int outputFd = open("saida.txt", O_RDONLY| O_TRUNC | O_CREAT, 0644);

    int errorFd = open("erros.txt", O_RDONLY | O_TRUNC | O_CREAT, 0644);



    dup2(inputFd, 0);
    close(inputFd);

    dup2(outputFd, 1);
    close(outputFd);

    dup2(errorFd, 2);
    close(errorFd);

    sleep(60);


    return 0;
}