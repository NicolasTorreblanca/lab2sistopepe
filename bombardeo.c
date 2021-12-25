#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){

  const char separador[2] = " ";
  char* entrada;
  entrada = strtok(argv[0], entrada);

  int i = 0;

// nombreEntrada nombre_salida inicial final  







  

  int cantidadParticulas = superior-inferior;

  float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
  
  int * arregloPos = (int*)malloc(cantidadParticulas*sizeof(int));
  
  int * arregloEn = (int*)malloc(cantidadParticulas*sizeof(int));  

  lectura(arregloEn, arregloPos,nombreEntrada,inferior, superior);
    
  bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas, cantidadParticulas,nombre_salida); 

  char* retorno = strcat(nombre_salida,);
	write(STDOUT_FILENO,retorno , 100); 

  free(arregloCeldas);
  free(arregloPos);
  free(arregloEn);

  return 0;

}


