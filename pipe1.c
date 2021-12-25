#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#include <sys/wait.h> 
#include <sys/types.h> 

#define LECTURA 0
#define ESCRITURA 1

int avance();


int calcular_N(int particulas,int procesos){

  int n;

  if(particulas % procesos == 0){
    n = particulas / procesos;
  }

  else{    
    int j = particulas % procesos;
    int particulas_corregidas = particulas - j;
    n = particulas_corregidas / procesos;
  }
  return n;
}

int avance(int* arreglo,int posicion_final){
  
  int avanzado = 0;

  for(int i = 0; i<posicion_final;i++){
    avanzado = avanzado + arreglo[i];
  }
  return avanzado;
}

void asignar_Particulas(int particulas,int procesos,int n, int* arreglo_particulas){

  if(particulas % procesos == 0){

      n = particulas / procesos;
      for(int i = 0; i<n ; i++){
        arreglo_particulas[i] = procesos;    
    }
  }

  else{
    int j = particulas % procesos;
    int particulas_corregidas = particulas - j;

    for(int i =0; i<n ; i++){
      arreglo_particulas[i] = procesos;
    }
    for(int k =0 ;k<j;k++){
      while(j>n){
        for(int i = 0; i<n ; i++){
          arreglo_particulas[i] = arreglo_particulas[i] + 1; 
        }
        j = j-n;        
      }
      arreglo_particulas[k] = arreglo_particulas[k] + 1; 
    }
  }

}



int padre_hijo(int* arreglo, int n,int contador){
  int status;

  int proceso_hijo = 0;
  int proceso_padre = 0;

  int posterior = 0;
  int anterior = 0;
  int pid1 = -1;


  for(int i = 0; i < n; i ++){
    int * pipesPH = (int*)malloc(sizeof(int)*2); 
    int * pipesHP = (int*)malloc(sizeof(int)*2); 
    pipe(pipesPH);
    pipe(pipesHP);


    pid1 = fork();

    if (pid1 == -1)
    {
        return 1;
    }

    if (pid1 == 0)
    {
        //PROCESO HIJO
        proceso_hijo = proceso_hijo +1;
        close(pipesPH[ESCRITURA]);
        close(pipesHP[LECTURA]);
        read(pipesPH[LECTURA],&arreglo[i],sizeof(arreglo[i]));
        anterior = avance(arreglo,i);
        posterior = avance(arreglo,i+1);
        printf("Trabajo desde : %d hasta %d\n",anterior,posterior);
        write(pipesHP[ESCRITURA],&posterior,sizeof(posterior));

        free(pipesHP);
        break;

    }else{
        proceso_padre = proceso_padre + 1;
        
        close(pipesPH[LECTURA]);
        close(pipesHP[ESCRITURA]);
        write(pipesPH[ESCRITURA], &arreglo[i],sizeof(arreglo[i]));
        wait(&status);
        read(pipesHP[LECTURA], &posterior, sizeof(posterior));
        printf("Mi hijo trabaja hasta: %d\n", posterior);

        free(pipesPH);

    }

      printf("\nPP : %d , PH : %d\n",proceso_padre,proceso_hijo);
  }
    
   
}




int main(){
  int particulas = 26;
  int procesos = 7; 
  int n  = calcular_N(particulas,procesos);
  int * arreglo = (int*)malloc(n*sizeof(int));

  asignar_Particulas(particulas,procesos,n,arreglo);

  int a = padre_hijo(arreglo,n,0);
  return 0;
  
}