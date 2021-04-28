#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    //pipe_fd[commandos-1][2]
    int pipe_fd[3][2];

    for (int i = 0; i < 4; i++) {
        if(pipe(pipe_fd[i]) != 0) {
            perror("pipe_fd");
            exit(1);
        }
    }
    
    //wc
    if (fork() == 0) {
        //fechar pipe_fds
        close(pipe_fd[0][0]);
        close(pipe_fd[0][1]);
        close(pipe_fd[1][0]);
        close(pipe_fd[1][1]);
        close(pipe_fd[2][1]);

        dup2(pipe_fd[2][0],0);
        close(pipe_fd[2][0]);

        execlp("wc","wc","-l",NULL);
        
        _exit(1);
    }
    //uniq
    if (fork() == 0) {
        //fechar pipe_fds
        close(pipe_fd[0][0]);
        close(pipe_fd[0][1]);
        close(pipe_fd[1][1]);
        close(pipe_fd[2][0]);

        dup2(pipe_fd[1][0], 0);
        close(pipe_fd[1][0]);
        dup2(pipe_fd[2][1], 1);
        close(pipe_fd[2][1]);

        execlp("uniq", "uniq", NULL);
        _exit(1);
    }
    //cut
    if (fork() == 0) {
        //fechar pipe_fds
        close(pipe_fd[0][1]);
        close(pipe_fd[1][0]);
        close(pipe_fd[2][0]);
        close(pipe_fd[2][1]);

        dup2(pipe_fd[0][0], 0);
        close(pipe_fd[0][0]);
        dup2(pipe_fd[1][1], 1);
        close(pipe_fd[1][1]);

        char * exec_args[] = {
            "cut",
            "-f7",
            "-d:",
            NULL,
        };

        execvp("cut", exec_args);
        _exit(1);
    }
    
    //grep
    if (fork() == 0) {
        //fechar os pipe_fds que nao estao a ser usados
        close(pipe_fd[0][0]);
        close(pipe_fd[1][0]);
        close(pipe_fd[1][1]);
        close(pipe_fd[2][0]);
        close(pipe_fd[2][1]);


        dup2(pipe_fd[0][1], 1);
        close(pipe_fd[0][1]);

        char * exec_args[] = {
            "grep",
            "-v",
            "^#",
            "/etc/passwd",
            NULL,
        };

        execvp("grep", exec_args);

        _exit(1);
    }

    //stdin(0) -> teclado
    //stdout(1) -> ecra
    //fd[1] -> escrita pipe_fd
    close(pipe_fd[0][1]);
    close(pipe_fd[1][1]);
    close(pipe_fd[2][1]);
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}