#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

int segundos_restantes;

void alarma(int signum) {
    printf("Tiempo finalizado.\n");
    exit(segundos_restantes);
}

int main(int argc, char* argv[]) {
    int primerNumero = atoi(argv[1]);
    int segundoNumero = atoi(argv[2]);
    int contador = primerNumero;
    
    segundos_restantes = segundoNumero - primerNumero;
    signal(SIGALRM, alarma);
    alarm(segundos_restantes);
    
    while (contador <= segundoNumero) {
        printf("Contador: %d\n", contador);
        sleep(1);
        contador++;
    }
    
    int pipe_fd = open("pipe_fifo", O_WRONLY);
    char buffer[20];
    sprintf(buffer, "%d", contador - 1);
    write(pipe_fd, buffer, strlen(buffer) + 1);
    close(pipe_fd);
    
    return 0;
}

