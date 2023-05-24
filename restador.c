#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int resultado = num1 - num2;
    
    int pipe_fd = open("pipe_fifo", O_WRONLY);
    char buffer[20];
    sprintf(buffer, "%d", resultado);
    write(pipe_fd, buffer, strlen(buffer) + 1);
    close(pipe_fd);
    
    return 0;
}

