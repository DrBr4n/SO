#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char * argv[]) {

    int fd = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644); 

    char fd_string[10];
    sprintf(fd_string, "%d", fd);

    execl("writeToFd", "writeToFd", fd_string, NULL); //ao usar excel o programa muda mas os recursos(fds, ...) sao mantidos visto que o processo é o mesmo
    
    return 0;
} 