#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int ctrl_c_counter = 0;
int time = 0;

void ctrl_c_handler(int signum) {
    ctrl_c_counter++;
    printf("sigint recebido... Tempo passado: %d\n", time);
}

void ctrl_slash_handler(int signum) {
    printf("sigquit recebido... CTRL+C recebidos: %d\n", ctrl_c_counter);
    _exit(0);
}

void sigalrm_handler(int signum) {
    printf("sigalrm recebido...\n");
    alarm(1);
    time++;
}


int main(int argc, char * argv[]) {

    if(signal(SIGINT, ctrl_c_handler) == SIG_ERR)
        perror("SIGINT: ");
    if(signal(SIGQUIT, ctrl_slash_handler) == SIG_ERR)
        perror("SIGQUIT: ");
    if(signal(SIGALRM, sigalrm_handler) == SIG_ERR)
        perror("SIGALRM: ");

    alarm(1);
    while (1){
        //alarm(1);
        pause();
    }
    
    return 0;
}