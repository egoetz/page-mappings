#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "You must pass a size and only a size as an arg.\n");
        return 1;
    }

    long pid = (long)getpid();
    fprintf(stderr, "PID of this process is %d\n", pid);

    unsigned int n;
    n = atoi(argv[1]);
    for(int i = 0; i < n; i++){
        char *buffer = (char *) malloc(getpagesize());
        buffer[0] = 0;
    }

    getchar();

    return 0;
}

