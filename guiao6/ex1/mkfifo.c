#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) { 

    //if (fork() == 0) {
    //    execlp("mkfifo", "mkfifo", argv[1], NULL);
    //}

    if (mkfifo(argv[1], 0666) < 0) {
        perror("mkfifo\n");
        return 1;
    }
    
    return 0;
}