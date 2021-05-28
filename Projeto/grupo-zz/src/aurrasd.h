//#include "parse_entry.h"

/**
 * Variaveis globais
 * @param rd_fifo descritor de ficheiro para extremo de leitura do fifo
 * @param wr_fifo descritor de ficheiro para extremo de escrita do fifo
*/
int rd_fifo;
int wr_fifo;


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