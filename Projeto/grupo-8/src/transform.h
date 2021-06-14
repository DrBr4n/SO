struct config {
    char * nome;
    char * exec;
};

struct config filtros[5];

/**
 * 
*/
void loadConf(char * name);

/**
 * 
*/
ssize_t readln(int fd, char *line, size_t size);

/**
 * 
*/
void oneFilter(int nArgs, char** args);

/**
 * 
*/
void multipleFilters(int nArgs, char** args);

