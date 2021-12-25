#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

#define LECTURA 0
#define ESCRITURA 1


int main(int argc, char *argv[]) {
    int * pipesPH = (int*)malloc(sizeof(int)*2); 
    int * pipesHP = (int*)malloc(sizeof(int)*2); 
    pipe(pipesPH);
    pipe(pipesHP);


    char* palabra = "Miguel_Mayorga Ivan_Tulilla Willy Laikita";

    char *const bufferPH[1]={palabra};

    char bufferHP[100];
    int status;
    int pid;
    
    pid = fork();
    //El hijo escribe y el padre lee, pero con exec y dup2
    if (pid == 0) {
        close(pipesPH[ESCRITURA]);
        close(pipesHP[LECTURA]);       

        read(pipesPH[LECTURA],bufferPH[0],sizeof(bufferPH));  
        dup2(pipesHP[ESCRITURA],STDOUT_FILENO); //STDOUT_FILENO = un int que tiene el descriptor de stdout.
           // no usamos lectura

        execvp("./hijo",bufferPH);
        printf("HOLA\n");
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("padre pregunta:");
        printf("Quien es la maquina? \n");

        close(pipesPH[LECTURA]);
        close(pipesHP[ESCRITURA]);
          
        write(pipesPH[ESCRITURA], bufferPH[0],sizeof(bufferPH));            

        
        wait(&status);
        read(pipesHP[LECTURA], bufferHP, 100); 
        
        //leemos el pipe y lo imprimimos
        printf("Hijo dice:\n%s",bufferHP);
    }


    return 0;
}
