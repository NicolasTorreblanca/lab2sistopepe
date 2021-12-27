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

void padre_hijo(int* arreglo, int n,int contador,char * nombre_entrada,char * nombreSalida,int cantidad_Celdas,float**pendientes){
  int status;

  int proceso_hijo = 0;
  int proceso_padre = 0;

  int posterior = 0;
  int anterior = 0;
  int pid1 = -1;
  
  for(int i = 0; i < n; i ++){
    int * pipesPH = (int*)malloc(sizeof(int)*2); 
    int * pipesHP = (int*)malloc(sizeof(int)*2);
    char aux[125];

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
        char buffPH[125];

        char celdas[12];
        sprintf(celdas, "%d", cantidad_Celdas);


        strcpy(buffPH,nombre_entrada);
        strcat(buffPH,esp);
        strcat(buffPH,nombreSalida);
        strcat(buffPH,esp);
        strcat(buffPH,celdas);
        strcat(buffPH,esp);
        strcat(buffPH,aux);

       
        char *args[3]={"./bomb",buffPH,NULL};

        printf("Se entrego :%s \n",args[1]);
 
        dup2(pipesHP[ESCRITURA],STDOUT_FILENO);
        execv(args[0],args);

        printf(" exec fallo \n");
        perror("exec ls failed");
        exit(EXIT_FAILURE);

        free(pipesHP);
        break;

    }else{
        proceso_padre = proceso_padre + 1;

        char bufferHP[100];      

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

        close(pipesPH[LECTURA]);
        close(pipesHP[ESCRITURA]);
        
        write(pipesPH[ESCRITURA], aux,sizeof(aux));

        wait(&status);
        
        read(pipesHP[LECTURA], bufferHP, 100);

        printf("Mi hijo escribio: %s\n", bufferHP);

        pendientes = actualizar_Arreglo(pendientes,cantidad_Celdas,bufferHP);     
        free(pipesPH);

        if(i+1 == n){  
          juntar_Arreglos(pendientes,cantidad_Celdas,n,nombreSalida);
        }

    }

      printf("\nPP : %d , PH : %d\n",proceso_padre,proceso_hijo);
  }
    
   
}



int main(){
  int particulas = 7;
  int procesos = 7;
  int cantidad_Celdas = 35;
  int n  = calcular_N(particulas,procesos);
  int * arreglo = (int*)malloc(n*sizeof(int));

  asignar_Particulas(particulas,procesos,n,arreglo);

  float** pendientes = (float**)malloc(n * sizeof(float*));

  for (int i = 0; i < n; i++){
    pendientes[i] = (float*)malloc(cantidad_Celdas * sizeof(float));
  }
 

  padre_hijo(arreglo,n,0,"test1_35.txt","output.txt",cantidad_Celdas,pendientes);
  
  return 0;
  
}