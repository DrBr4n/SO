/**
 * @struct Estrutura com as configuraçẽs de cada filtro
 * @param nome nome do filtro
 * @param exec nome do binario do filtro
*/
struct config {
    char * nome;
    char * exec;
};

/**
 * Array de configurações de filtros
*/
struct config filtros[5];

/**
 * Carrega os nomes e binários dos filtros para a estrutura de configuração
 * @param name path para o ficheiro de configurações
*/
void loadConf(char * name);

/**
 * Ler byte a byte do descritor de ficheiros dado para o buffer dado
 * @param fd descritor de ficheiros de onde vai ler
 * @param line buffer para onde vai ler
 * @param size tamanho do buffer dado
 * @return numero de bytes lidos
*/
ssize_t readln(int fd, char *line, size_t size);


/**
 * Aplica os filtros presentes no array de strings com os argumentos
 * @param nArgs número de argumentos do array de strings
 * @param args array de strings com os argumentos passados pelo cliente
*/
void apllyFilters(int nArgs, char** args);

