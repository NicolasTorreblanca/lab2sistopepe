#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h> //define varios tipos de datos como pid_t

#define LECTURA 0
#define ESCRITURA 1


int main(int argc, char* argv[]){

    int pid1 = -1;
    pid1 = fork();
    int status;

    if(pid1<0){
        exit(-1);
    }

    if(pid1==0){
        
        printf("soy el hijo, tengo pid %d y fork retorno %d\n",getpid(),pid1);
        printf("el pid de mi padre es: %d\n",getppid());
        execl("./ejecutable","./ejecutable",NULL);
    }
    else{
        wait(&status);
        printf("soy el padre, tengo pid %d y fork me retorno %d\n",getpid(),pid1);
        
        printf("fin de programa\n");
        
    }
    return 0;
}