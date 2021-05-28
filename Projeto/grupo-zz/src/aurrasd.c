#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "aurrasd.h"
//#include "parse_entry.h"

//server
int main(int argc, char * argv[]) {

    //loadConf("../etc/aurrasd.conf");

    setup();


    debug(rd_fifo);


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

}

void setup() {
    /**
     * Associa rotina de tratamento sigint_handler ao sinal SIGINT
     * Associa rotina de tratamento sigterm_handler ao sinal SIGTERM
    */
    if(signal(SIGINT, sigint_handler) == SIG_ERR) perror("Erro na associacao do handler do SIGINT");
    if(signal(SIGTERM, sigterm_handler) == SIG_ERR) perror("Erro na associacao do handler do SIGTERM");

    /**
     * Criar o nammed pipe com o nome fifo
    */
    if(mkfifo("fifo", 0666) < 0) perror("mkfifo\n");

    /**
     * Criar descritor de ficheiro para o extremo de leitura do fifo
    */
    rd_fifo = open("fifo", O_RDONLY);
    if ((rd_fifo < 0)) perror("Erro ao abrir fifo em modo leitura\n");

    /**
     * Criar descritor de ficheiro para o extremo de escrita do fifo
     * Tecnica para o servidor ficar sempre aberto
    */
    wr_fifo = open("fifo", O_WRONLY);
    if ((wr_fifo < 0)) perror("Erro ao abrir fifo em modo escrita\n");
}

void shutdown() {
    /**
     * Fechar o descritor de ficheiro do extremo de leitura do fifo
    */
    close(rd_fifo);

    /**
     * Fechar o descritor de ficheiro do extremo de escrita do fifo
     * Causa o fecho do servidor
    */
    close(wr_fifo);

    /**
     * Apagar o fifo
    */
    unlink("fifo");
}

void debug(int fd) {

    char buf[1024];

    int line_bytes = 0;

    while ((line_bytes = readln(fd, buf, 1024)) > 0) {
        //escrever para o ecra
        write(STDOUT_FILENO, buf, line_bytes);
    }

    /**
     * Ler do extremo de leitura do fifo e escrever para o stdout
    */
    //char buf[1024];
    //int bytes_read;
    //while ((bytes_read = read(rd_fifo, buf, 1024)) > 0) {
    //    write(1, buf, bytes_read);
    //}
}