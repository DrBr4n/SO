#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "person.h"

int new_person(char* name, int age){

    int fd = open("people.bin", O_CREAT | O_APPEND | O_RDWR, 0644);

    if (fd < 0) {
        perror("Error while oppening file on new_person()");
        return 1;
    }

    Person p;
    strcpy(p.name, name);
    p.age = age;

    if(write(fd, &p, sizeof(Person)) < 0){
        perror("Writing error on new_person()");
        return 1;
    }


    close(fd);

    return 0;
}

int person_change_age(char* name, int age){

    int fd = open("people.bin", O_RDWR, 0644);
    if (fd < 0) {
        perror("Error while oppening file on person_change_age()");
        return 1;
    }

    Person p;
    int nBytes = 0;

    do {
        nBytes = read(fd, &p, sizeof(Person));
    } while (strcmp(p.name, name) != 0 && nBytes > 0);

    //go back 4b (-sizeof(int))
    lseek(fd, -sizeof(int), SEEK_CUR);

    if(write(fd, &age, sizeof(int)) < 0){
        perror("Writing error on person_change_age()");
        return 1;
    }

    close(fd);

    return 0;
}

int person_change_age_v2(long pos, int age){

    int fd = open("people.bin", O_RDWR, 0644);

    if (fd < 0) {
        perror("Error while oppening file on person_change_age_v2()");
        return 1;
    }

    Person p;
    lseek(fd, (pos - 1) * sizeof(Person), SEEK_SET);

    //jump bytes of name (sizeof(name))
    lseek(fd, sizeof(p.name), SEEK_CUR);

    if(write(fd, &age, sizeof(int)) < 0){
        perror("Writing error on person_change_age_v2()");
        return 1; 
    }

    close(fd);

    return 0;
}

void read_file() {

    int fd = open("people.bin", O_RDWR, 0644);

    if (fd < 0) {
        perror("Error while oppening file on read_persons()");
    }

    Person p;
    int nBytes = 0;
    int i = 0;

    while ((nBytes = read(fd, &p, sizeof(Person))) > 0) {
        printf("p%d.name: %s\n", i, p.name);
        printf("p%d.age: %d\n", i, p.age);
        i++;
    }

    close(fd);
}