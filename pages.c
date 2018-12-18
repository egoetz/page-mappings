#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define PAGEMAP_ENTRY_SIZE 8

int main(int argc, char **argv){
    pid_t pid;
    if(argc == 1){
        pid = getpid();
    }
    else if(argc == 2){
        pid = (pid_t) atoi(argv[1]);
    }
    else{
        fprintf(stderr, "Given more than one argument. You can only pass a pid.");
        return 1;
    }

    char maps_path[80];
    char pagemap_path[80];
    snprintf(maps_path, 80, "/proc/%d/maps", pid);
    snprintf(pagemap_path, 80, "/proc/%d/pagemap", pid);

    //get positive integer n as command line arg
    FILE *maps = fopen(maps_path, "r");
    FILE *pagemap = fopen(pagemap_path, "rb");
    if(maps == NULL || pagemap == NULL){
        printf("Failed file opening.\n");
        return 2;
    }

    char *line = NULL;
    ssize_t len = 0;
    short is_stack;
    short is_heap;
    uint64_t start;
    uint64_t end;
    uint64_t starting_page_number;
    uint64_t ending_page_number;
    uint64_t page_offset;
    uint64_t pagemap_info;
    uint64_t mappings;
    while(getline(&line, &len, maps) != -1){
        if(strstr(line, "[stack]") != NULL){
            is_stack = 1;
            sscanf(line, "%lx-%lx", &start, &end);
            fprintf(stderr, "Stack address range: 0x%lx to 0x%lx\n", start, end);
        }
        if(strstr(line, "[heap]") != NULL){
            is_heap = 1;
            sscanf(line, "%lx-%lx", &start, &end);
            fprintf(stderr, "Heap address range: 0x%lx to 0x%lx\n", start, end);
        }
        if(is_stack || is_heap){
            starting_page_number = start / getpagesize();
            if(end % getpagesize() == 0){
                ending_page_number = end / getpagesize();
            }
            else{
                ending_page_number = end / getpagesize() + 1;
            }
            for(uint64_t i = 0; starting_page_number + i < ending_page_number; i++){
                page_offset = (starting_page_number + i) * PAGEMAP_ENTRY_SIZE;
                fseek(pagemap, page_offset, SEEK_SET);
                if(fread(&mappings, 8, 1, pagemap) == 0){
                    printf("fread failed\n");
                    return 3;
                }
                if((mappings >> 63) == 1){
                    fprintf(stderr, "\t0x%lx -> 0x%lx\n", starting_page_number + i, ((mappings << 9) >> 9));
                }
            }
        }
        is_stack = 0;
        is_heap = 0;
    }
    return 0;
}
