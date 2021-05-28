#include <sys/types.h>

#define INTERNAL_BUFF_SIZE 100

/**
 * Recebe um endereço de um apontador para um buffer com uma ou mais linhas
 * @return apontador para um array de x strings
*/
char** parse_entry(char** position);

/**
 * 
*/
ssize_t readln(int fd, char *line, size_t size);

/**
 * 
*/
int readch(int fd, char * buf);

