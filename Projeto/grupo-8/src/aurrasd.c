#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "aurrasd.h"

//server
int main(int argc, char * argv[]) {

    //loadConf("../etc/aurrasd.conf");

    setup();


    debug(rd_fifoCS);


    return 0;
}

void sigint_handler(int signum) {
    printf("sigint recebido\n");
    kill(getpid(), SIGTERM);
}

void sigterm_handler(int signum) {
    printf("sigterm recebido, encerrando\n");
    shutdown();
    //kill(getpid(), SIGKILL);
}

void loadConf(char * name) {

    //int conf = open(name, O_RDONLY);

}

void setup() {
    /**
     * Associa rotina de tratamento sigint_handler ao sinal SIGINT
     * Associa rotina de tratamento sigterm_handler ao sinal SIGTERM
    */
    if(signal(SIGINT, sigint_handler) == SIG_ERR) perror("Erro na associacao do handler do SIGINT");
    if(signal(SIGTERM, sigterm_handler) == SIG_ERR) perror("Erro na associacao do handler do SIGTERM");

    /**
     * Criar os nammed pipes
    */
    if(mkfifo("fifoCS", 0666) < 0) perror("mkfifoCS\n");
    if(mkfifo("fifoSC", 0666) < 0) perror("mkfifoSC\n");

    /**
     * Criar descritor de ficheiro para o extremo de leitura do fifo
    */
    rd_fifoCS = open("fifoCS", O_RDONLY);
    if ((rd_fifoCS < 0)) perror("Erro ao abrir fifoCS em modo leitura\n");

    /**
     * Criar descritor de ficheiro para o extremo de escrita do fifo
     * Tecnica para o servidor ficar sempre aberto
    */
    wr_fifoCS = open("fifoCS", O_WRONLY);
    if ((wr_fifoCS < 0)) perror("Erro ao abrir fifoCS em modo escrita\n");
}

void shutdown() {
    /**
     * Fechar o descritor de ficheiro do extremo de leitura do fifo
    */
    close(rd_fifoCS);

    /**
     * Fechar o descritor de ficheiro do extremo de escrita do fifo
     * Causa o fecho do servidor
    */
    close(wr_fifoCS);

    /**
     * Apagar os fifos
    */
    unlink("fifoCS");
    unlink("fifoSC");
}

void debug(int fd) {

    /**
     * Ler do extremo de leitura do fifo e escrever para o stdout
    */
    char buf[1024];
    int bytes_read;

    while ((bytes_read = read(fd, buf, 1024)) > 0) {

        parse_entry(buf);

    }
}

void parse_entry(char* buf) {
    int numBytes[10];
    int nArgs = 0;
    int bytes = 0;

    //conta quantos argumentos existem e quantos bytes cada um tem
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == ' ') {
            nArgs++;
            bytes = 0;
        }
        else {
            bytes++;
            numBytes[nArgs] = bytes;
        }
    }

    char * args[nArgs];
    int c = 0;

    //aloca o numero de bytes necessarios para cada arg e preenche o com a string
    for (int i = 0; i < nArgs; i++) {
        args[i] = malloc(numBytes[i] * sizeof(char));
        for (int k = 0; buf[c] != ' '; k++, c++) {
            args[i][k] = buf[c];
        }
        c++;
    }

    comandoSingular(args);
    for (int i = 0; i < nArgs; i++) {
        printf("args[%d]: %s\n", i, args[i]);
    }

    if (strcmp(args[0], "status") == 0) {
        status();
    }
    
    //if (fork() == 0) {
    //    
    //    execlp(args[0], args[0], args[1], NULL);
    //    _exit(0);
    //}
}

void status() {
    wr_fifoSC = open("fifoSC", O_WRONLY);
    if ((wr_fifoSC < 0)) perror("Erro ao abrir fifoCS em modo escrita\n");

    char * buffer = "this is some \ndummy text\njust\nto see\n ";
    int nbytes = 0;
    for (; buffer[nbytes] != '\0'; nbytes++);

    write(wr_fifoSC, buffer, nbytes);


    close(wr_fifoSC);
}

void comandoSingular(char* args[]) {
    if (fork() == 0) {
        //int fd = open("teste", O_CREAT, 0666);
        //printf("no comando");
        //char * r = "< ";
        //r = strcat(r, args[1]);
        //args[1] = strcat(r, " >");

        //printf("Conaargs[1]%s\n", args[1]);
        //printf("Conaargs[2]%s\n", args[2]);

        //char * argv[]= {  
        //    "aurrasd-echo", 
        //    args[1],
        //    args[2],
        //    NULL
        //};
        //execv("bin/aurrasd-filters/", argv);
        execl("aurrasd-filters/aurrasd-echo", "aurrasd-echo", "< ../../samples/sample-1-so.m4a >", "output.mp3", NULL);
        _exit(1);
        //./aurrasd-echo < ../../samples/sample-1-so.m4a > output.mp3

    }
}
//bash$ bin/aurrasd-filters/aurrasd-echo < samples/samples-1.m4a > output.mp3
/*
./aurras transform samples/sample-1.m4a output.m4a alto eco rapido
args[0]: transform
args[1]: samples/sample-1.m4a
args[2]: output.m4a
args[3]: alto
args[4]: eco
args[5]: rapido
*/