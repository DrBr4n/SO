#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    //vamos usar distribuição de processos por linhas:
    //padrao mais adequeado: sequencial, concorrente ou cadeia? -> concorrente 
    int value = atoi(argv[1]);

    int rows = 10;

    int cols = 10000;


    //matriz alocada na stack (usar malloc para alocar na heap)
    int matrix[rows][cols];


    //popular matriz com valores aleatorios
    int rand_max = 10000;

    for (int i = 0; i < rows; i++){

        for (int j = 0; j < cols; j++){

            matrix[i][j] = rand() % rand_max;
        }
    }
    printf("Matrix populated.\n");

    //procurar o valor (dividir o trabalho por linhas)
    int pids[rows];
    int pid;
    for (int i = 0; i < rows; i++) {
        if ((pid = fork()) == 0) {
            //guarda pid para pids
            pids[i] = getpid();
            printf("Creating  pid:  %d\n", getpid());
            //i = linha onde vai procurar
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == value)
                    _exit(1); //encontrei = 1
            }

            _exit(0); //não encontrei = 0
        }
    }

    //aguardar que os processos filho acabem (#nprocs = #nlinhas)
    int status;
    for (int i = 0; i < rows; i++) {
        printf("Waiting  pid:  %d\n", pids[i]);
        pid_t terminated_pid = waitpid(pids[i], &status, 0);

        //se o processo-filho completou a execução, verifica o valor do codigo de saida
        if(WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 1) {
                //filho encontrou
                printf("[pai] process %d exited. found number at row: %d\n", terminated_pid, i);
            } else {
                //filho nao encontrou
                printf("[pai] process %d exited. nothing found\n", terminated_pid);
            }
        } else {
            printf("Algo correu mal");
        }
    }
    return 0;
}
/*
pontos essenciais do guiao:
-padroes de execução
-noção pontos chave: copia do processo pai, descritores tambem sao herdados, os pids sao diferentes
*/