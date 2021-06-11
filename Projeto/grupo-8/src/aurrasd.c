#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "aurrasd.h"

//server
int main(int argc, char * argv[]) {

    configPath = argv[1];
    filterPath = argv[2];

    loadConf(configPath); 

    setup();

    char buf[1024];
    int bytes_read;

    while ((bytes_read = read(rd_fifoCS, buf, 1024)) > 0) {

        parse_entry(buf);

    }

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
    char buffer[60];
    
    for (int i = 0; i < 5 ; i++) {
        
        readln(conf, buffer, 60);

        char * subString = strtok(buffer, " ");

        filtros[i].nome = malloc(sizeof(subString));
        strcpy(filtros[i].nome , subString);
        subString = strtok(NULL, " ");
        subString = strtok(NULL, " ");
        filtros[i].max = atoi(subString);
        filtros[i].current = 0;
    }
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

void parse_entry(char* buf) {

    int nArgs = 0;
    int bytes = 0;

    //conta numero de argumentos
    for (int i = 0; buf[i] != '\0'; i++) 
        if (buf[i] == ' ')
            nArgs++;
    
    int numBytes[nArgs];

    //conta quantos argumentos existem e quantos bytes cada um tem
    int indexNumBytes = 0;
    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == ' ') {
            indexNumBytes++;
            bytes = 0;
        }
        else {
            bytes++;
            numBytes[indexNumBytes] = bytes;
        }
    }

    char * args[nArgs];

    //aloca o numero de bytes necessarios para cada arg e preenche o com a string
    int index = 0;
    for (int i = 0; i < nArgs; i++) {
        args[i] = malloc(numBytes[i] * sizeof(char));
        for (int k = 0; buf[index] != ' '; k++, index++) {
            args[i][k] = buf[index];
        }
        index++;
    }

    args[nArgs] = malloc(sizeof(char *));
    args[nArgs++] = configPath;
    args[nArgs] = malloc(sizeof(char *));
    args[nArgs++] = filterPath;
    args[nArgs] = malloc(sizeof(NULL));
    args[nArgs++] = NULL;

    //FOR DEBUG, printing args on server
    for (int i = 0; i < nArgs; i++) {
        printf("args[%d]: %s\n", i, args[i]);
    }

    if (strcmp(args[0], "status") == 0) {
        status();
    }

    if (strcmp(args[0], "transform") == 0) {
        transform(args);
    }

    //addToQueue();
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

void transform (char ** args) {

    if (fork() == 0) {
        
        execv("transform", args);

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