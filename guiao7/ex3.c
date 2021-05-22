#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void sigalrm_handler(int signum) {
    printf("sigalrm recebido...\n");
    kill(getpid(), SIGKILL);
}

int main(int argc, char *argv[]) {

    if(signal(SIGALRM, sigalrm_handler) == SIG_ERR)
        perror("SIGALRM: ");

    int pids[argc - 2];

    alarm(10);

    for (int i = 2; i < argc; i++) {

        if(fork() == 0){

            alarm(10);

            if (fork() == 0) {
                pids[i - 2] = getpid();

                execlp("grep", "grep", argv[1], argv[i], NULL);
    
                _exit(1);
            }
        }
    }

    int status;
    int pid_done = wait(&status);

    //if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0) {
    //    for (int i = 0; i < argc - 2; i++) {
    //        if (pids[i] != pid_done)
    //            kill(pids[i], SIGKILL);
    //    }
    //}
    return 0;
}