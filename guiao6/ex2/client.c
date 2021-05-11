#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {

    //abrir o pipe fifo
    int fifo_fd = open("fifo", O_WRONLY);
    
    if (fifo_fd < 0) 
        perror("open");

    int c = 0;
    for (int i = 0; argv[1][i] != 0; i++) {
        c++;
    }

    write(fifo_fd, argv[1], c);
    
    close(fifo_fd);

    return 0;
}