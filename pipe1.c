#include "funciones.h"
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#include <sys/wait.h> 
#include <sys/types.h> 

#define LECTURA 0
#define ESCRITURA 1

void padre_hijo(int* arreglo, int n,int contador,char * nombre_entrada,char * nombreSalida,int cantidad_Celdas){
  int status;

  int proceso_hijo = 0;
  int proceso_padre = 0;

  int posterior = 0;
  int anterior = 0;
  int pid1 = -1;

  char aux[125];
  char bufferHP[100];

  for(int i = 0; i < n; i ++){
    int * pipesPH = (int*)malloc(sizeof(int)*2); 
    int * pipesHP = (int*)malloc(sizeof(int)*2); 
    pipe(pipesPH);
    pipe(pipesHP);


    pid1 = fork();

    if (pid1 == -1)
    {       
        break;
    }

    if (pid1 == 0)
    {
        //PROCESO HIJO
        proceso_hijo = proceso_hijo +1;
        close(pipesPH[ESCRITURA]);
        close(pipesHP[LECTURA]);

        read(pipesPH[LECTURA],aux,sizeof(aux));

        char* esp = " ";        
        char mensaje[125];

        char celdas[12];
        sprintf(celdas, "%d", cantidad_Celdas);


        strcpy(mensaje,nombre_entrada);
        strcat(mensaje,esp);
        strcat(mensaje,nombreSalida);
        strcat(mensaje,esp);
        strcat(mensaje,celdas);
        strcat(mensaje,esp);
        strcat(mensaje,aux);


        printf("entrega : %s \n",mensaje);

        char* entrega;
        strcpy(entrega,mensaje);
       
        char *const bufferPH[1]={entrega};


        printf("entrega : %s \n",entrega);

        printf("entrando al exec \n");
        dup2(pipesHP[ESCRITURA],STDOUT_FILENO); 
        execvp("./bomb",bufferPH);


        printf(" exec fallo \n");
        perror("exec ls failed");
        exit(EXIT_FAILURE);


        free(pipesHP);
        break;

    }else{
        proceso_padre = proceso_padre + 1;

        posterior = avance(arreglo,i+1);
        anterior = avance(arreglo,i);

               
        char ant_str[12];
        sprintf(ant_str, "%d", anterior);

        char post_str[12];
        sprintf(post_str, "%d", posterior);

        char iter[12];
        sprintf(iter, "%d",i);

        char* esp = " ";

        char* aux = strcat(ant_str,esp);

        aux = strcat(aux,post_str);

        aux = strcat(aux,esp);

        aux = strcat(aux,iter);
              
        printf("Trabajo entre %s \n",aux);

        close(pipesPH[LECTURA]);
        close(pipesHP[ESCRITURA]);
        
        write(pipesPH[ESCRITURA], aux,sizeof(aux));

        wait(&status);
        read(pipesHP[LECTURA], bufferHP, 100);


        printf("Mi hijo escribio: %s\n", bufferHP);
        free(pipesPH);

        if(i+1 == n){  
          for(int j =0;j<n;j++){
          printf(" %d " , arreglo[j]);
          }
        }

    }

      printf("\nPP : %d , PH : %d\n",proceso_padre,proceso_hijo);
  }
    
   
}



int main(){
  int particulas = 5;
  int procesos = 5;
  int cantidad_Celdas = 35;
  int n  = calcular_N(particulas,procesos);
  int * arreglo = (int*)malloc(n*sizeof(int));

  asignar_Particulas(particulas,procesos,n,arreglo);

  padre_hijo(arreglo,n,0,"test1_35.txt","output.txt",cantidad_Celdas);

  float** arr = (float**)malloc(n * sizeof(float*));

  for (i = 0; i < n; i++){
    arr[i] = (float*)malloc(cantidad_Celdas * sizeof(float));
  }
 

  
  return 0;
  
}