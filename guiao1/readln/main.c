#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "readln.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]){

    char buf[BUF_SIZE];

    int fd = open(argv[1], O_RDONLY);

    int line_bytes = 0;

    while ((line_bytes = readlnv2(fd, buf, BUF_SIZE)) > 0) {
        //escrever para o ecra
        write(STDOUT_FILENO, buf, line_bytes);
    }

    return 0;
}