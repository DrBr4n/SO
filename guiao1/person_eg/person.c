#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct Person {

    char name[200];

    int age;

} Person;


int main(int argc, char* argv[]){

    int fd = open("persons.bin", O_CREAT | O_APPEND | O_RDWR, 0644);


    //check fd < 0
    if (fd < 0){ 
        perror("Ficheiro não aberto");
        return 1;
    }
    

    Person p1;
    
    strcpy(p1.name, "Maria Mourinho");
    
    p1.age = 32;


    printf("p1.name: %s\n", p1.name);
    printf("p1.age: %d\n", p1.age);
    printf("sizeof(Person): %ld\n", sizeof(Person));

    if(write(fd, &p1, sizeof(Person)) < 0) {
        perror("write");
    }

    //1. voltar ao inicio do ficheiro
    //lseek(fd, 0, SEEK_SET); //fd.pos = 0
    
    //2. deslocar o fd sizeof(Person) bytes para a esquerda
    lseek(fd, -sizeof(Person), SEEK_CUR);

    Person p1_read;
    if(read(fd, &p1_read, sizeof(Person)) > 0){
        printf("p1_read.name: %s\n", p1_read.name);
        printf("p1_read.age: %d\n", p1_read.age);
    }
    
    close(fd);

    return 0;
}