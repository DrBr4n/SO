#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int pids[argc-2];

    for (int i = 2; i < argc; i++) {
        if(fork() == 0){
            pids[i - 2] = getpid();

            //int fifo_fd = open("fifo", O_WRONLY);
            //if (fifo_fd < 0) 
            //perror("open");
            //dup2(fifo_fd, 1);
            
            execlp("grep", "grep", argv[1], argv[i], NULL);

            _exit(1);
        }
    }

    int status;
    int pid_done = wait(&status);

    if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0) {

        for (int i = 0; i < argc - 2; i++) {
            if (pids[i] != pid_done)
                kill(pids[i], SIGKILL);
        }
    }

    //int fifo_fd = open("fifo", O_RDONLY);
    //if (fifo_fd < 0) 
    //    perror("open");

    //char buf[1024];
    //int bytes;
    //while ((bytes = read(fifo_fd, buf, bytes)) > 0)
    //{
    //    write(1, buf, bytes);        
    //}

    return 0;
}