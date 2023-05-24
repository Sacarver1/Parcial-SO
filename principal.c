#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num1, num2;
    int opcion;
    
    printf("Ingrese dos números: ");
    scanf("%d %d", &num1, &num2);
    
    printf("Opciones:\n");
    printf("1. Sumar los números\n");
    printf("2. Restar los números\n");
    printf("3. Contadores hasta los números\n");
    printf("4. Contar el primer número y esperar el tiempo del segundo\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);
    
    char num1_str[10];
    char num2_str[10];
    sprintf(num1_str, "%d", num1);
    sprintf(num2_str, "%d", num2);
    
    char* programa;
    
    switch (opcion) {
        case 1:
            programa = "./sumador";
            break;
        case 2:
            programa = "./restador";
            break;
        case 3:
            programa = "./contador";
            break;
        case 4:
            programa = "./temporizador";
            break;
        default:
            printf("Opción inválida.\n");
            return 0;
    }
    
    int pipe_fd[2];
    pipe(pipe_fd);
    
    if (fork() == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execlp(programa, programa, num1_str, num2_str, NULL);
    } else {
        close(pipe_fd[1]);
        char buffer[20];
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Resultado: %s\n", buffer);
        close(pipe_fd[0]);
    }
    
    return 0;
}

