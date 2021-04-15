#include <unistd.h>
#include <fcntl.h> 
#include <stdlib.h>

#define MAXBUFFER 1

int main(int argc, char *argv[]){

    int bytesRead = 0;

    //char buffer[MAXBUFFER];
    char * buffer = (char *) malloc(sizeof(char) * MAXBUFFER);

    while((bytesRead = read(STDIN_FILENO, buffer, MAXBUFFER)) > 0) //read from input
        write(STDOUT_FILENO, buffer, MAXBUFFER);                   //copy to output

    free(buffer);

    return 0;
} 