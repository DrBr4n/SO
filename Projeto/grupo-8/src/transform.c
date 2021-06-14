#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include "transform.h"


int main(int argc, char * argv[]) {     

    loadConf(argv[argc - 2]);

    //oneFilter(argc, argv);

    multipleFilters(argc, argv);

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

void multipleFilters(int nArgs, char ** args) {

    for (int i = 0; i <= nArgs; i++) {
        printf("transformArgs[%d]: %s\n", i, args[i]);
    }
    printf("nArgs: %d\n", nArgs);
    int pid;

    char * path = args[nArgs - 1];

    sleep(30);

    for (int i = 0; i < nArgs - 5; i++) {

        //create pipes
        int nPipes = nArgs - 6;
        int pipes[nPipes][2];
        for (int i = 0; i < nPipes; i++) {
            pipe(pipes[i]);
        }
        
        
        if (fork() == 0) {
            if ((pid = fork()) == 0) {

                if (i == 0) { //first filter
                    //setup input
                    int input = open(args[1], O_RDWR); 
                    dup2(input, 0);
                    close(input);

                    //setup output
                    dup2(pipes[i][1], 1);
                }

                else if(i == nArgs - 6) { //last filter
                    //setup input
                    dup2(pipes[i][0], 0);

                    //setup output
                    int output = open(args[2], O_WRONLY | O_CREAT , 0666);
                    dup2(output, 1);    
                    close(output);

                }
                else {
                    //setup input
                    dup2(pipes[i][0], 0);

                    //setup output
                    dup2(pipes[i][1], 1);
                }

                //close pipes
                for (int k = 0; k < nPipes; k++) {
                    close(pipes[k][0]);
                    close(pipes[k][1]);
                }

                path = args[nArgs - 1];

                for (int k = 0; k < 5; k++) {
                    if(strcmp(args[i + 3], filtros[k].nome) == 0) {
                        strcat(path, filtros[k].exec);
                        execlp(path, filtros[k].exec, NULL);
                    }
                }
            }
            
            waitpid(pid, NULL, 0);
            kill(getpid(), -9);
        }
    }
}

/*
transformArgs[0]: transform
transformArgs[1]: ../samples/sample-3-lcc.m4a
transformArgs[2]: ../tmp/output.mp3
transformArgs[3]: rapido
transformArgs[4]: alto
transformArgs[5]: eco
transformArgs[6]: ../etc/aurrasd.conf
transformArgs[7]: aurrasd-filters/
transformArgs[8]: (null)
nArgs: 8

../samples/sample-3-lcc.m4a -> rapido -> |pipe| <- alto -> |pipe| <- eco -> ../tmp/ouput.mp3


*/