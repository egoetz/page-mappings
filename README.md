# page-mappings
A program that prints the current page mappings for the stack and heap of a given process.

Please note that this is a Linux specific program.

# Creating Mappings
The stack_allocate.c file and the heap_allocate.c file are testing files. They allow the user to allocate a specific number of pages on the stack or the heap respectively. One created, the programs' executibles can be called as follows:
```
./stack_allocate <number of pages>
./heap_allocate <number of pages>
```
Note that these processes will not exit unless the user enters a character. This is to allow the user to use pages to see the page mappings for these processes. Each process automatically prints its pid so that the pid can be easily entered into the pages process.

# Obtaining the Mappings
The pages.c file contains the code that will actually find a process' virtual memory address for the stack and the heap and translate them to physical memory addresses. Once the user compiles the program, they can run it with the following format:
```
sudo ./pages
sudo ./pages <process number>
```
The first format will give the address mappings for the pages process itself. The second format will give the address mappings for the process specified. Here, one can add the process number of the stack_allocate process or the heap_allocate process.
