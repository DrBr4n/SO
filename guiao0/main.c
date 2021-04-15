/*
    1. Pretende-se criar um programa que permita manipular um vector de inteiros com os seguintes requisitos:
    
        -Suportar a seguinte API:
            void fill(int* vector, int size, int value);
            int find(int* vector, int size, int value);
        -A função main() deve estar isolada num ficheiro .c independente.
        -Deve incluir um header file onde define a estrutura e a API descritos anteriormente
        -O programa deve ser compilado usando uma Makefile.

*/
#include <stdio.h>
#include "lib.h"
#include "funcs.c"

int main() {

    int size = 5;

    int value = 2;

    int array[size];

    int arrayy[size];

    vector = array;

    fill(vector, size, value);

    int r = find(vector, size, value);
    
    return 0;
}