#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char * argv) {

    //abrir o pipe fifo
    int fifo_fd = open("fifo", O_RDONLY);
    
    if (fifo_fd < 0) 
        perror("open");
    
    printf("Debug: Fifo is open\n");

    //ler do stdin e escreve para fifo_fd
    char buf[1024];
    int bytes_read;

    while ((bytes_read = read(fifo_fd, buf, 1024)) > 0) {
        write(0, buf, bytes_read);
    }
    
    close(fifo_fd);

    return 0;
}