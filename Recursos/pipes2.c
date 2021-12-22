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
    int* pipes = (int*)malloc(sizeof(int)*2); //pipe para que hijo lea y padre escriba
    int* pipes2 = (int*)malloc(sizeof(int)*2);//pipe para que hijo escriba y padre lea
    pipe(pipes);
    pipe(pipes2);
    printf("pipe tiene los siguientes valores: %d %d \n",pipes[LECTURA],pipes[ESCRITURA]);
    char mensaje[30] = "hola proceso hijo";
    char mensajeConfirmado [30] = "listo padre, recibi el mensaje";
    
    char* mensajerecibido = (char*)malloc(sizeof(char)*30);
    char* ack = (char*)malloc(sizeof(char)*30);
    pid1 = fork();
    if(pid1==0){
        //cerraremos los lados de los pipes que no usaremos
        close(pipes[ESCRITURA]);
        close(pipes2[LECTURA]);
        //escribimos en el pipe2 y leemos del pipe1
        write(pipes2[ESCRITURA],mensajeConfirmado,30*sizeof(char));
        read(pipes[LECTURA],mensajerecibido,30*sizeof(char));
        printf("mi padre dice: %s\n",mensajerecibido);  
    }
    else{
        printf("proceso padre\n");
        close(pipes[LECTURA]);
        close(pipes2[ESCRITURA]);
        write(pipes[ESCRITURA],mensaje,30*sizeof(char));
        wait(&status);
        read(pipes2[LECTURA],ack, 30*sizeof(char));
        printf("mi hijo me dice: %s\n", ack);
        //close(pipes[ESCRITURA]);
    }

    return 0;
}