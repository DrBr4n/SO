#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char * argv[]) {

    int pipe_fd[2];

    if(pipe(pipe_fd) != 0) {
        perror("pipe: ");
        return 1;
    }

    if (fork() == 0) {
        char * s = "ola";
        sleep(5);
        write(pipe_fd[1], &s, 3);
        close(pipe_fd[1]);
        printf("child pid: %d\n", getpid());
        _exit(0);
    }
    
    wait(NULL);
    printf("parent pid: %d\n", getpid());
    char * p;
    read(pipe_fd[0], &p, 3);
    printf("Wasup: %s\n", p);


    close(pipe_fd[0]);

    return 0;
}