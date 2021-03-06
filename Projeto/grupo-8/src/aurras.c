#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h> 

//client
int main(int argc, char * argv[]) {

    /**
     * Imprimir informações de uso do client
    */
    if (argc == 1) {
        printf("./aurras status\n./aurras transform ../samples/sample-1-so.m4a ../output/output.mp3 alto rapido eco\n");
        return 0;
        
    }

    /**
     * Criar descritor de ficheiro para o extremo de escrita do fifo
    */
    int wr_fifoCS = open("../tmp/fifoCS", O_WRONLY); //caso chame o programa dentro da pasta bin (./aurras)
    if (wr_fifoCS < 0) wr_fifoCS = open("tmp/fifoCS", O_WRONLY); //caso chame o programa fora da pasta bin (bin/aurras)
    if (wr_fifoCS < 0) perror("Erro ao abrir fifo em modo escrita\n");

    /**
     * Contar numero de bytes da linha
    */
    int nbytes = 0;
    for (int i = 1; i < argc; i++) {
        for (int k = 0; argv[i][k] != 0; k++) {
            nbytes++;
        }
        nbytes++;
    }
    nbytes++;

    /**
     * Concatenar todos os argvs necessarios numa linha
    */
    char * res = malloc(nbytes * sizeof(char));
    for (int i = 1; i < argc; i++) {
        strcat(res, argv[i]);
        strcat(res, "\n");
    }

    /**
     * Escrever a mensagem para o fifo
    */
    write(wr_fifoCS, res, nbytes);

    /**
     * Libertar memoria
     * Fechar descritores abertos
    */
    free(res);
    close(wr_fifoCS);

    //caso o comando seja status
    if(!strcmp(argv[1], "status")) {
        int rd_fifoStatus = open("../tmp/fifoStatus", O_RDONLY);
        if (rd_fifoStatus < 0) rd_fifoStatus = open("tmp/fifoStatus", O_RDONLY);
        if (rd_fifoStatus < 0) perror("Erro ao abrir fifoStatus em modo leitura\n");

        char buf[1024];
        int bytes_read = 0;

        while ((bytes_read = read(rd_fifoStatus, buf, 1024)) > 0) {
            write(1, buf, bytes_read);
        }
    }
    else {
        int rd_fifoSC = open("../tmp/fifoSC", O_RDONLY);
        if (rd_fifoSC < 0) rd_fifoSC = open("tmp/fifoSC", O_RDONLY);
        if (rd_fifoSC < 0) perror("Erro ao abrir fifoSC em modo leitura\n");

        char buf[1024];
        int bytes_read = 0;

        while ((bytes_read = read(rd_fifoSC, buf, 1024)) > 0) {
            write(1, buf, bytes_read);
        }
    }

    return 0;
}