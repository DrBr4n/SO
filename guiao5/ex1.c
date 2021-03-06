#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char * argv[]) {

    int pipe_fd[2];

    if(pipe(pipe_fd) != 0) {
        perror("pipe: ");
        return 1;
    }
    
    char * s = "ola";
    write(pipe_fd[1], &s, 3);
    close(pipe_fd[1]);

    sleep(5);
    if (fork() == 0)
    {
        char * p;
        read(pipe_fd[0], &p, 3);
        printf("Wasup: %s\n", p);
        printf("child pid: %d\n", getpid());
        _exit(0);
    }
    
    wait(NULL);
    printf("parent pid: %d\n", getpid());

    close(pipe_fd[0]);


    return 0;
}