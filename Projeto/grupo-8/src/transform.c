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

/*

*/
void loadConf(char * name) { //configs hardcoded

    //int conf = open(name, O_RDONLY);

    //char buffer[1024];
    //read(conf, buffer,1024);

    //printf("buffer: %s", buffer);

    config.alto = "aurrasd-gain-double";
    config.baixo = "aurrasd-gain-half";
    config.eco = "aurrasd-echo";
    config.rapido = "aurrasd-tempo-double";
    config.lento = "aurrasd-tempo-half";

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

    if (!strcmp(args[3], "alto")) {
        strcat(path, config.alto);
        argv[0] = config.alto;
    }
    else if (!strcmp(args[3], "baixo")) {
        strcat(path, config.baixo);
        argv[0] = config.baixo;
    }
    else if (!strcmp(args[3], "eco")) {
        strcat(path, config.eco);
        argv[0] = config.eco;
    }
    else if (!strcmp(args[3], "rapido")) {
        strcat(path, config.rapido);
        argv[0] = config.rapido;
    }
    else if (!strcmp(args[3], "lento")) {
        strcat(path, config.lento);
        argv[0] = config.lento;
    }

    execvp(path, argv);
}
