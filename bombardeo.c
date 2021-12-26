#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]){
/*
  const char separador[2] = " ";
  char* entrada;
  entrada = strtok(argv[0], entrada);

  int i = 0;

// nombreEntrada nombre_salida cantidadCeldas  inicial final iteracion
// Ej : test1_35.txt output.txt 35 0 4 0

*/
  int cantidadCeldas = 35;

  char* nombreEntrada = "test1_35.txt";
  char* nombre_salida = "output.txt";

  int superior = 4;
  
  int inferior = 0;

  iteracion = 0;


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


