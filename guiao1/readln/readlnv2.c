#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define INTERNAL_BUFF_SIZE 100

char internal_buff[INTERNAL_BUFF_SIZE];
int next_pos = 0;
int last_read_bytes = 0;

int readch(int fd, char * buf) {

    //se não, le do disco para o interno, atualiza vars, escreve no buf 1byte e retorna 1 
    if(next_pos == last_read_bytes){

        int bytes = 0;  

        if ((bytes = read(fd, internal_buff, INTERNAL_BUFF_SIZE)) < 1) {
            return 1;
        }

        next_pos = 0;
        
        last_read_bytes = bytes;

    }

    *buf = internal_buff[next_pos];
    next_pos++;

    return 0;
}

ssize_t readlnv2(int fd, char *line, size_t size) {

    //ler byte a byte do fd(descritor de ficheiro) 
    int next_pos = 0;

    int read_bytes = 0;

    while (next_pos < size && readch(fd, line + next_pos) == 0) {
        
        read_bytes++;
        // - até encontrar \n
        if (line[next_pos] == '\n') break;

        next_pos++;
    }

    //retornar o numero de bytes lidos
    return read_bytes;
}