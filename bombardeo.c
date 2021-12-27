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

  const char s[2] = " ";
  char *entrada= strtok(argv[1],s);

  int i = 0;
  char nombreEntrada[25];
  char nombre_salida[25];
  char celdas[25];
  char ant_str[25];
  char sup_str[25];
  char iter_in[25];  


  printf("xd\n");

  while( entrada != NULL ) {
      
      if(i == 0){
        strcpy(nombreEntrada,entrada);   
        i = i+1;    
      }
      else if(i == 1){
        strcpy(nombre_salida,entrada);    
        i = i+1;    
      }
      else if(i == 2){
        strcpy(celdas,entrada);
        i = i+1;    
      }
      else if(i == 3){
        strcpy(ant_str,entrada);
        i = i+1;    
      }
      else if(i == 4){  
        strcpy(sup_str,entrada);
        i=i+1;
      }
      else if(i == 5){
        strcpy(iter_in,entrada);
      } 
      entrada = strtok(NULL, s);   
  }


  int cantidadCeldas = atoi(celdas);
  int superior = atoi(sup_str);
  int inferior = atoi(ant_str);
  int iteracion = atoi(iter_in);
  int diferencia = superior - inferior;

  float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
  
  int * arregloPos = (int*)malloc(diferencia*sizeof(int));
  
  int * arregloEn = (int*)malloc(diferencia*sizeof(int));  

  lectura(arregloEn,arregloPos,nombreEntrada,inferior,superior);

  for(int i=0;i<diferencia;i++){
    printf("%d ",arregloEn[i]);
    printf(" %d \n",arregloPos[i]);
  }


  bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas,diferencia,nombre_salida); 

  printf("fin escritura \n");
  char iter[12];
  sprintf(iter, " %d",iteracion);

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


