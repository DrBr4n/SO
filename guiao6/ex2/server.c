#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    //abrir o ficheiro log
    int log_fd = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (log_fd < 0) 
        perror("open log");
    
    printf("Debug: Log is open\n");

    //criar o fifo
    if (mkfifo("fifo", 0666) < 0) {
        perror("mkfifo\n");
        return 1;
    }

    //abrir o pipe fifo para ler
    int fifo_fd = open("fifo", O_RDONLY);
    //abrir o pipe fifo para escrita, so para nao fechar o server
    int fifo_fd_write = open("fifo", O_WRONLY);
    
    if (fifo_fd < 0) 
        perror("open fifo");
    
    printf("Debug: Fifo is open\n");

    //ler do stdin e escreve para log
    char buf[1024];
    int bytes_read;

    while ((bytes_read = read(fifo_fd, buf, 1024)) > 0) {
        write(log_fd, buf, bytes_read);
    }
    
    close(fifo_fd);
    unlink("fifo");
    close(log_fd);

    return 0;
}