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

    int conf = open(name, O_RDONLY);

    char buffer[1024];
    read(conf, buffer,1024);

    printf("buffer: %s", buffer);
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

        int input = open("/home/bruno/Documents/SO/Projeto/grupo-8/samples/sample-1-so.m4a", O_RDWR);
        int output = open("/home/bruno/Documents/SO/Projeto/grupo-8/tmp/output.mp3", O_WRONLY | O_CREAT , 0666);
        dup2(input, 0);
        dup2(output, 1);    
        close(input);
        close(output);

        char * path = "/home/bruno/Documents/SO/Projeto/grupo-8/bin/aurrasd-filters/aurrasd-echo";

        char * argv[]= {"aurrasd-echo", NULL};

        sleep(30);

        execvp(path, argv);
    }
}
