#include <unistd.h>   // chamadas ao sistema: defs e decls essenciais 
#include <sys/wait.h> // chamadas wait*() e macros relacionadas 
#include <stdio.h>

int main(int argc, char * argv[]) {

    int status;
    int nproc = 10;
    pid_t pid;

    for (int i = 1; i <= nproc; i++) {
    
        if((pid = fork()) == 0) {
            printf("child: -child %d pid: %d\n", i, getpid());

        } else { 

            int terminated_pid = wait(&status);
            printf("main: -child %d pid: %d\n", WEXITSTATUS(status), terminated_pid);
            _exit(i - 1);
        }
    }

    _exit(10);

    return 0;
}