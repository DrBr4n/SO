#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFER 100

int main(int argc, char *argv[]){

    //open origin file
    int originFile = open(argv[1], O_RDONLY);
    if (originFile < 0) {
        perror("open from");
        return 1;
    }

    //open destination file
    int destinationFile = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (destinationFile < 0) {
        perror("open to");
        return 1;
    }
    
    int bytesRead = 0;
    
    //char buffer[MAXBUFFER];

    char * buffer = (char *) malloc(sizeof(char) * MAXBUFFER);

    while((bytesRead = read(originFile, buffer, MAXBUFFER)) > 0) //read from origin file
        write(destinationFile, buffer, MAXBUFFER);             //copy to destination file

    free(buffer);

    //close files
    close(originFile);
    close(destinationFile);

    return 0;
}