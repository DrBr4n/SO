#include <stdio.h>

void fill(int* vector, int size, int value) {

    for (int i = 0; i < size; i++)
    {
        *vector = value;
        vector++;
    }
}

int find(int* vector, int size, int value) {

    int r = -1;

    for (int i = 0; i < size; i++)
    {
        if (*vector == value)
        {
            r = i;
        }
        vector++;
    }
    return r;
}

void read(int* vector, int size) {

    for (int i = 0; i < size; i++) 
    {
        printf("%d\n", *vector);
        vector++;
    }
}