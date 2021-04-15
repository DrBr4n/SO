#include <unistd.h>   // chamadas ao sistema: defs e decls essenciais 
#include <sys/wait.h> // chamadas wait*() e macros relacionadas 
#include <stdio.h>

int main(int argc, char * argv[]) {

    int status;
    int nproc = 10;
    pid_t pid;

    for (int i = 1; i <= nproc; i++) {
    
        if((pid = fork()) == 0) { //se filho:
            //-print do seu pid
            printf("child: -child %d pid: %d\n", i, getpid());
            //-sai com codigo de saida igual o numero sequencial
            _exit(i);

        } else { //se pai:
            //-esperar que o processo filho termine
            int terminated_pid = wait(&status);

            //-imprime codigo de saida do processo filho
            printf("main: -child %d pid: %d\n", WEXITSTATUS(status), terminated_pid);
        }
    }
    return 0;
}