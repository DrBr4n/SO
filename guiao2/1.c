#include <unistd.h>   // chamadas ao sistema: defs e decls essenciais 
#include <sys/wait.h> // chamadas wait*() e macros relacionadas 
#include <stdio.h>

int main (int argc, char * argv[]) {

    //imprimir PID do processo
    printf("pid: %d\n", getpid());

    //imprimir PID do processo pai
    printf("parent pid: %d\n", getppid());

    return 0;
}