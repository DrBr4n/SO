/**
 * Variaveis globais
*/
//descritor de ficheiro para extremo de leitura do fifo client -> server
int rd_fifoCS;

//descritor de ficheiro para extremo de escrita do fifo client -> server
int wr_fifoCS;

//descritor de ficheiro para extremo de leitura do fifo server -> client
int rd_fifoSC;

//descritor de ficheiro para extremo de escrita do fifo server -> client
int wr_fifoSC;

//descritor de ficheiro para extremo de leitura do fifoStatus
int rd_fifoStatus;

//descritor de ficheiro para extremo de escrita do fifoStatus
int wr_fifoStatus;

//string com o path da pasta dos filtros
char * filterPath;

//string com o path do ficheiro de configurações do servidor
char * configPath;

//string com o nome do fifo Client -> Server
char * fifoCS;

//string com o nome do fifo Server -> Client
char * fifoSC;

//string com o nome do fifoStatus
char * fifoStatus;

/**
 * @struct Estrutura com as configuraçẽs de cada filtro
 * @param nome nome do filtro
 * @param max número máximo de instancias
 * @param current número de instancias a ser usadas
*/
struct config {
    char * nome;
    int max;
    int current;
};

/**
 * Array de configurações de filtros
*/
struct config filtros[5];

/**
 * Número de filtros
*/
int nFiltros; 

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
 * Associa rotinas de tratamento de sinais\n
 * Cria fifos\n
 * Inicializa as variaveis globais: fifoCS, fifoSC, fifoStatus, rd_fifoCS, wr_fifoCS
 * @param args vai receber o argv[0] da main para verificar em que pasta está a correr o servidor
*/
void setup(char * args);

/**
 * Fecha descritores do fifo Client -> Server
 * Apaga todos os fifos
*/
void shutdown();

/**
 * Recebe uma string de argumentos e separa-a num array de strings com um argumento por string
 * @param buf String que vai ser recebida
*/
void parse_entry(char* buf);

/**
 * Comunica com o cliente através do fifo Server -> Client e envia o número de instancias a correr e máximas de cada filtro
*/
void status();

/**
 * Envia mensagem de pending/processing ao cliente e corre outro binario(transform) através de um exec
 * @param nArgs número de argumentos do array de strings
 * @param args array de strings com os argumentos passados pelo cliente
*/
void transform(int nArgs, char ** args);

/**
 * Incrementa na estrutura de configuração de cada filtro o número de filtros que vai usar
 * @param nArgs número de argumentos do array de strings
 * @param args array de strings com os argumentos passados pelo cliente
*/
void incrementInstances(int nArgs, char ** args);

/**
 * Decrementa na estrutura de configuração de cada filtro o número de filtros que foi usado
 * @param nArgs número de argumentos do array de strings
 * @param args array de strings com os argumentos passados pelo cliente
*/
void decrementInstances(int nArgs, char ** args);

/**
 * Ler byte a byte do descritor de ficheiros dado para o buffer dado
 * @param fd descritor de ficheiros de onde vai ler
 * @param line buffer para onde vai ler
 * @param size tamanho do buffer dado
 * @return numero de bytes lidos
*/
ssize_t readln(int fd, char *line, size_t size);