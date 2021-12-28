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

  //Primero se procesa el string que se recibe de entrada

  const char s[2] = " ";
  char *entrada= strtok(argv[0],s);

  int i = 0;
  char nombreEntrada[25];
  char nombre_salida[25];
  char celdas[25];
  char ant_str[25];
  char sup_str[25];
  char iter_in[25];  

  //Para ello de divide cada elemento del string y se almacena en variables

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

  //Se declaran los arreglos de memoria dinamica

  float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
  int * arregloPos = (int*)malloc(diferencia*sizeof(int));
  int * arregloEn = (int*)malloc(diferencia*sizeof(int)); 

  //Se realiza la lectura del archivo de las particulas
  //Sirve para llenar los arreglos de energia y posiciones 

  lectura(arregloEn,arregloPos,nombreEntrada,inferior,superior);

  //Con estos arreglos se puede calcular el bombardeo con las 
  //Particulas especificas
  //Se escribe un archivo de escritura parcial
  //Donde se indica cual es el resultado que se obtuvo usando 

  bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas,diferencia,nombre_salida); 

  //Se genera un String que sera escrito por el hijo en el pipe 
  // que lo conecta con el padre

  char iter[12];
  sprintf(iter, " %d",iteracion);

  char salida[100];

  strcpy(salida,nombre_salida);
  strcat(salida,iter);

  //Se escribe en el pipe

  write(STDOUT_FILENO,salida, 100); 

  //Se libera la memoria dinamica

  free(arregloCeldas);
  free(arregloPos);
  free(arregloEn);

  //Termina este proceso hijo

  return 0;

}


