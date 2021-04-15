#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    
    if (write(atoi(argv[1]), "ola", 3) < 0) {
        perror("write");
    }
    
    return 0;
}