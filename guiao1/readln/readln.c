#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

ssize_t readln(int fd, char *line, size_t size) {

    //ler byte a byte do fd(descritor de ficheiro) 
    int next_pos = 0;

    int read_bytes = 0;

    while (next_pos < size && read(fd, line + next_pos, 1) > 0) {
        
        read_bytes++;
        // - até encontrar \n
        if (line[next_pos] == '\n') break;

        next_pos++;
    }

    //retornar o numero de bytes lidos
    return read_bytes;
}