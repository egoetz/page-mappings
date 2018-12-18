#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*
 * Adds a specified number of pages to the stack.
 * Precodition: Must give an arguement representing the number of pages. 
 * Postcondition: Will return 1 if incorrect number of args is passed.
 * Will exit successfully and return 0 after a char input.
 * Side effects: Allocates the specified number of pages on the stack.
*/
int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "You must pass a size and only a size as an arg.\n");
        return 1;
    }

    long pid = (long)getpid();
    fprintf(stderr, "PID of this process is %d\n", pid);

    unsigned int n;
    n = atoi(argv[1]);
    char allocated_array[getpagesize() * n];
    for(int i = 0; i < n; i++){
        allocated_array[getpagesize() * i] = 0;
    }

    getchar();

    return 0;
}

