//#include "parse_entry.h"

/**
 * Variaveis globais
 * @param rd_fifoCS descritor de ficheiro para extremo de leitura do fifo client -> server
 * @param wr_fifoCS descritor de ficheiro para extremo de escrita do fifo client -> server
 * @param rd_fifoSC descritor de ficheiro para extremo de leitura do fifo server -> client
 * @param wr_fifoSC descritor de ficheiro para extremo de escrita do fifo server -> client
*/
int rd_fifoCS;
int wr_fifoCS;
int rd_fifoSC;
int wr_fifoSC;

/**
 * Handler para o sinal SIGINT
*/
void sigint_handler(int signum);

/**
 * Handler para o sinal SIGTERM
*/
void sigterm_handler(int signum);

/**
 * Carrega as configurações do servidor
 * @param name path para o ficheiro de configurações
*/
void loadConf(char * name);

/**
 * Associa rotinas de tratamento de sinais
 * Cria fifo
 * Inicializa variaveis globais
*/
void setup();

/**
 * Fecha descritores abertos
 * Apaga fifo
*/
void shutdown();

/**
 * 
*/
void debug(int fd);

/**
 * 
*/
void parse_entry(char* buf);

/**
 * 
*/
void status();