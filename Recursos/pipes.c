#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h> //define varios tipos de datos como pid_t

#define LECTURA 0
#define ESCRITURA 1


int main(int argc, char** argv){

    int pid1 = -1;
    
    int status;
    int* pipes = (int*)malloc(sizeof(int)*2);
    pipe(pipes);

    printf("pipe tiene los siguientes valores: %d %d \n",pipes[LECTURA],pipes[ESCRITURA]);
    char mensaje[30] = "hola proceso hijo";
    char* mensajerecibido = (char*) malloc(sizeof(char)*30);
    pid1 = fork();

    //para este caso el padré escribirá y el hijo leerá
    
    if(pid1==0){
        //como el hijo solo lee, no usará el pipe de escritura, se cierra
        close(pipes[ESCRITURA]);
        read(pipes[LECTURA],mensajerecibido,30*sizeof(char));
        printf("mi padre dice: %s\n",mensajerecibido);  
    }
    else{
        //el padre no lee, asi que se cierra ese pipe
        printf("proceso padre\n");
        close(pipes[LECTURA]);
        printf("Escribiendo en el pipe\n");
        write(pipes[ESCRITURA],mensaje,30*sizeof(char));
        wait(&status);
        //close(pipes[ESCRITURA]);
    }

    return 0;
}