#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <sys/types.h> 

#define LECTURA 0
#define ESCRITURA 1

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
      for(int i = 0; i<n ; i++){
          printf("%d",arreglo_particulas[i]); 
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
    for(int i = 0; i<n ; i++){
      printf("%d",arreglo_particulas[i]); 
  }
  }

}

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

int* actualizar(int* arreglo,int n){

  int * actualizado = (int*)malloc(n*sizeof(int));

  for(int i = 0;i<n;i++){
    actualizado[i] = arreglo[i] + 1;
  }
  free(arreglo);
  return actualizado;
}

void asignar_Particulas(int particulas,int procesos,int n, int* arreglo_particulas){

  if(particulas % procesos == 0){
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


int main(){
  int particulas = 26;
  int procesos = 7; 
  int n  = calcular_N(particulas,procesos);
  int * arreglo = (int*)malloc(n*sizeof(int));

  asignar_Particulas(particulas,procesos,n,arreglo);

  return 0;
  
}