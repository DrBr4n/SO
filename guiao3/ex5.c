#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    for (int i = 1; i < argc; i++) {
        if (fork() == 0) {
            execlp(argv[i],argv[i],NULL);
            perror("exec");
            _exit(1);
        }
    }

    for (int i = 0; i < argc; i++) {
        int status = 0;
        wait(&status);
    }

    return 0;
}