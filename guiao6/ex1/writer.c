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
    
    printf("Debug: Fifo is open\n");

    //ler do stdin e escreve para fifo_fd
    char buf[1024];
    int bytes_read;

    while ((bytes_read = read(0, buf, 1024)) > 0) {
        write(fifo_fd, buf, bytes_read);
    }
    
    close(fifo_fd);

    return 0;
}