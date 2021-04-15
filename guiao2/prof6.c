#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    // ./ex6 <valor>    ./ex6 20
    int value = atai(agrv[1]);
    int rows = 10;
    int cols = 10000;

    //matriz alocada na stack
    int matrix[rows][cols];

    //popular matriz com valores aleatorios
    int rand_max = 10000;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix[i][j] = rand() % rand_max;
        }
    }

    printf("Done.\n");
    //procurar o valor na matriz de forma concorrente (dividir trabalho por linhas)

    for (int i = 0; i < rows; i++) {
        if (fork() == 0) {
            //i = indice da linha onde vai procurar (copia de memória do processo-pai)
            printf("[pid %d] row: %d\n", getpid(), i);

            //percore as colunas ate encontrar o valor
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == value) {
                    _exit(i); //encontrei é codigo igual ao numero da linha
                }
            }
            _exit(255); //nao encontrei poderia ser codigo 255
        }
    }
    //Aguardar pela terminação dos processos filho (#procs = #linhas)
    int status;

    for (int i = 0; i < rows; i++) {

        pid_t terminated_pid = wait(&status);

        if (WIFEXITED(status)) {
            
            if (WEXITSTATUS(status) < 255) {
                //filho encontrou
                printf("[pai] process %d exited. found number at row: %d\n", terminated_pid, WEXITSTATUS(status));
            } else {
                //filho nao encontrou
                printf("[pai] process %d exited, nothing found\n", terminated_pid);
            }
            
        } else {
            //algo correu mal
            printf("oops");
        }
    }
}