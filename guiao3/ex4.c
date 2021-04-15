#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {

    char * exec_args[] = {
        "sopa",
        "arg1",
        "arg2",
        "arg3",
        "arg4",
        NULL,
    };

    execv("3", exec_args);

    return 0;
}