#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char * argv[]) {
    
    if (fork() == 0)
    {
        printf("child pid: %d\n", getpid());
        _exit(0);
    }
    
    wait(NULL);
    printf("parent pid: %d\n", getpid());

    return 0;
}