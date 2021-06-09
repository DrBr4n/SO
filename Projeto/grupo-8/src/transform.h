struct confs {
    char * alto;
    char * baixo;
    char * eco;
    char * rapido;
    char * lento;
};

struct confs config;

/**
 * 
*/
void status();

/**
 * 
*/
void oneFilter(int nArgs, char** args);

void loadConf(char * name);