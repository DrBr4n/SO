#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //O_WRONLY etc..
#include <unistd.h> //open and close

//client
int main(int argc, char * argv[]) {

    if (argc == 1) {
        printf("./aurras status\n./aurras transform input-filename output-filename filter-id-1 filter-id-2 ...\n");
        return 0;
        
    }


    /**
     * Criar descritor de ficheiro para o extremo de escrita do fifo
    */
    int wr_fifoCS = open("fifoCS", O_WRONLY);
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
        strcat(res, " ");
    }
    //strcat(res, "\n");

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

    if (strcmp(argv[1], "status") == 0) {
        int rd_fifoSC = open("fifoSC", O_RDONLY);
        if (rd_fifoSC < 0) perror("Erro ao abrir fifoSC em modo leitura\n");

        char buf[1024];
        int bytes_read = 0;

        while ((bytes_read = read(rd_fifoSC, buf, 1024)) > 0) {
            write(1, buf, bytes_read);
        }

        close(rd_fifoSC);
    }
    
    return 0;
}