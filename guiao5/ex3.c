#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char * argv[]) {
    
    int pipe_fd[2];

    if (pipe(pipe_fd) != 0) {
        perror("pipe ");
        return 1;
    }
    


    if (fork() == 0)
    {
        //fechar no descritor de escrita
        close(pipe_fd[1]);

        //stdin -> pipe_fd[0]
        dup2(pipe_fd[0], 0);

        //fechar pipe_fd[0]
        close(pipe_fd[0]);

        execlp("wc", "wc", NULL);

        _exit(1);
    }
    
    wait(NULL);
    printf("parent pid: %d\n", getpid());

    //fecha descritor de leitura
    close(pipe_fd[0]);

    char buf[10];
    int bytes;
    while ((bytes = read(0, buf, bytes)) > 0)
    {
        write(pipe_fd[1], buf, bytes);        
    }
    

    return 0;
}