#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  int superior = 5;
  
  int inferior = 0;

  int diferencia = superior - inferior;

  int iteracion = 0;


  float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
  
  int * arregloPos = (int*)malloc(diferencia*sizeof(int));
  
  int * arregloEn = (int*)malloc(diferencia*sizeof(int));  

  printf("previa lectura \n");

  lectura(arregloEn,arregloPos,nombreEntrada,inferior,superior);

  for(int i=0;i<diferencia;i++){
    printf("%d ",arregloEn[i]);
    printf(" %d \n",arregloPos[i]);
  }

  printf("post lectura \n");  

  bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas,diferencia,nombre_salida); 

  printf("fin escritura \n");
  char iter[12];
  sprintf(iter, " %d",iteracion);

  printf("nombre_salida : %s, it: %s \n",nombre_salida,iter);

  char salida[100];

  strcpy(salida,nombre_salida);
  strcat(salida,iter);

  printf("nombre_salida : %s \n",salida);  


  write(STDOUT_FILENO,salida, 100); 

  free(arregloCeldas);
  free(arregloPos);
  free(arregloEn);

  return 0;

}


