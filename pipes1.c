#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h> 

#define LECTURA 0
#define ESCRITURA 1

// PROGRAMA PARA IR PROBANDO COMO FUNCIONAN LOS PROCESOS Y PIPES

int main(){
    int status;
    int numerito = 333;
    int newNumerito = 0;
    int pid1 = -1;
    // PIPES
    int * pipesPH = (int*)malloc(sizeof(int)*2); //pipe para que hijo lea y padre escriba
    int * pipesHP = (int*)malloc(sizeof(int)*2); //pipe para que hijo escriba y padre lea
    pipe(pipesPH);
    pipe(pipesHP);

    printf("Pipe tiene los siguientes valores: %d %d \n",pipesPH[LECTURA],pipesPH[ESCRITURA]);

    pid1 = fork();

    if (pid1 == -1)
    {
        return 1;
    }

    if (pid1 == 0)
    {
        //PROCESO HIJO
        printf("Proceso Hijo\n");
        close(pipesPH[ESCRITURA]);
        close(pipesHP[LECTURA]);
        read(pipesPH[LECTURA],&numerito,sizeof(numerito));
        printf("Mi padre dice: %d\n",numerito);
        newNumerito = numerito * 2;
        write(pipesHP[ESCRITURA],&newNumerito,sizeof(newNumerito));

    }else{
        //PROCESO PADRE
        printf("Proceso Padre\n");
        close(pipesPH[LECTURA]);
        close(pipesHP[ESCRITURA]);
        printf("Escribiendo en el pipe\n");
        write(pipesPH[ESCRITURA], &numerito,sizeof(numerito));
        wait(&status);
        read(pipesHP[LECTURA], &newNumerito, sizeof(newNumerito));
        printf("Mi hijo me dice: %d\n", newNumerito);

    }
    return 0;
}