struct config {
    char * nome;
    char * exec;
};

struct config filtros[5];

/**
 * 
*/
void status();

/**
 * 
*/
void oneFilter(int nArgs, char** args);

/**
 * 
*/
void loadConf(char * name);

/**
 * 
*/
ssize_t readln(int fd, char *line, size_t size);