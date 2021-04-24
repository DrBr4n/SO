#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char * argv[]) {

    int pipe_fd[2];

    if(pipe(pipe_fd) != 0) {
        perror("pipe: ");
        return 1;
    }

    if (fork() == 0)
    {
        printf("child pid: %d\n", getpid());
        _exit(0);
    }
    
    wait(NULL);
    printf("parent pid: %d\n", getpid(

    //close(pipe_fd[1]);

    //close(pipe_fd[0]);
    //sleep(30);

    return 0;
}