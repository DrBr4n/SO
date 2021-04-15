#include <unistd.h>   // chamadas ao sistema: defs e decls essenciais 
#include <sys/wait.h> // chamadas wait*() e macros relacionadas 
#include <stdio.h>

int main (int argc, char * argv[]) {

    //criar processo filho

    int pid;

    if((pid = fork()) == 0) {
        printf("pida: %d\n", getpid());

        printf("parent pida: %d\n", getppid());

        _exit(5);

    } else {
        printf("pid: %d\n", getpid());

        printf("parent pid: %d\n", getppid());

        printf("child pid: %d\n", pid);

        int status;
        int terminated_pid = wait(&status);
        
        printf("child process: %d, exit code: %d\n", terminated_pid, WEXITSTATUS(status));

    }
    return 0;
}