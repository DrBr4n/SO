#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int my_system(char * command) {
    //separar o commando por espaços strsep

    /*
    char * f;
    char * exec_arg[10];
    char * c;

    c = strdup(command);

    for (int i = 0; (f = strsep(&c, " ")) != NULL; i++) {
        strcpy(f, exec_arg[i]);
        printf("%s\n", f);
    }
    */

    char * exec_args[] = {
        "ls",
        "-l",
        NULL,
    };
    int pid;
    if ((pid = fork()) == 0) {
        execvp(exec_args[0], exec_args);
        _exit(1);
    }

    int status = 0;
    waitpid(pid,&status,0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return -1;
}


int main(int argc, char * argv[]) {

    char * command = "ls -l";

    for (int i = 0; i < 2; i++) {
        int res = my_system(command);
    }

    return 0;
}