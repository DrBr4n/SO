#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //O_WRONLY etc..
#include <unistd.h> //open and close

//clientrm
int main(int argc, char * argv[]) {

    /**
     * Criar descritor de ficheiro para o extremo de escrita do fifo
     * Tecnica para o servidor ficar sempre aberto
    */
    int wr_fifo = open("fifo", O_WRONLY);
    if (wr_fifo < 0) perror("Erro ao abrir fifo em modo escrita\n");


    /**
     * Enviar linha para o servidor
    */
    int nbytes = 0;
    for (int i = 0; argv[1][i] != 0; i++) {
        nbytes++;
    }
    //dar new line ao fim de cada mensagem
    strcat(argv[1], "\n");
    nbytes += 2;
    write(wr_fifo, argv[1], nbytes);

    close(wr_fifo);

    return 0;
}