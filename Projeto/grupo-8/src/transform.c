#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "transform.h"


int main(int argc, char * argv[]) {     

    loadConf(argv[argc - 2]);

    oneFilter(argc, argv);

}

void loadConf(char * name) {

    int conf = open(name, O_RDONLY);
    char buffer[60];
    
    for (int i = 0; i < 5 ; i++) {    

        readln(conf, buffer, 60);

        char * subString = strtok(buffer, " ");
        filtros[i].nome = malloc(sizeof(subString));
        strcpy(filtros[i].nome , subString);

        subString = strtok(NULL, " ");
        filtros[i].exec = malloc(sizeof(subString));
        strcpy(filtros[i].exec, subString);
    }
}

void oneFilter(int nArgs, char* args[]) { //processos estao a ficar em modo zombie (<defunct>), verificar exitstatus ou wait(null) might work

    int input = open(args[1], O_RDWR);
    int output = open(args[2], O_WRONLY | O_CREAT , 0666); 
    dup2(input, 0);
    close(input);
    dup2(output, 1);    
    close(output);

    char * path = args[nArgs - 1];
    char * argv[] = {"", NULL};

    for (int i = 0; i < 5; i++) {
        if(strcmp(args[3], filtros[i].nome) == 0) {
            strcat(path, filtros[i].exec);
            argv[0] = filtros[i].exec;
        }
    }
    
    execvp(path, argv);
}

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
