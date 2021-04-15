#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "person.h"

int main(int argc, char* argv[]){
    
    if (strcmp(argv[1], "-i") == 0) {
        int p = new_person(argv[2], atoi(argv[3]));
        if (p == 1) perror("Error inserting new person");
    }

    if (strcmp(argv[1], "-u") == 0) {
        //int p = person_change_age(argv[2], atoi(argv[3]));
        int p = person_change_age_v2(atol(argv[2]), atoi(argv[3]));
        if (p == 1) perror("Error changing age");
    }

    if (strcmp(argv[1], "-r") == 0) read_file();

    return 0;
}