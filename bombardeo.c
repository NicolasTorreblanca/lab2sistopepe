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

float impacto(float energiaInicial, int energiaParticula, int cantidadCeldas, int posCelda, int posParticula){
    float newEnergia = energiaInicial + (1000*energiaParticula)/(cantidadCeldas*sqrtf((float)(abs(posParticula-posCelda) + 1)));
    return newEnergia;
}

void bombardeo(float * arregloCeldas, int * arregloPos, int * arregloEn, int cantidadCeldas, int cantidadParticulas,int diferencia,char * nombreSalida,char* iteracion,char*salida){

    float energiaInicial;
    float newEnergia;
    for (int i = 0; i < diferencia; i++)
    {
        for (int j = 0; j < diferencia; j++)
        {
            energiaInicial = arregloCeldas[j];
            newEnergia = impacto(energiaInicial, arregloEn[i], cantidadCeldas, j, arregloPos[i]);
            //Verificacion de caso de MIN_ENERGY
            if (newEnergia >= 0.001/cantidadCeldas)
            {
                arregloCeldas[j] = newEnergia;
            }
        }
    }
    salida = escritura_Parcial(arregloCeldas,cantidadCeldas,nombreSalida,iteracion);

}

void lectura(int * arregloEn, int * arregloPos, char * nombreEntrada, int pos_inicial,int pos_final){
    int auxiliarPos;

    //Lectura del archivo
    FILE * archivoEntrada = fopen(nombreEntrada, "r");
    if (archivoEntrada == NULL)
    {
        perror("\nArchivo No Existente\n");
    }else{
        for (int i = pos_inicial-1; i < pos_final-1; i++)
        {
            fscanf(archivoEntrada, "%d", &arregloPos[i]);
            fscanf(archivoEntrada, "%d", &arregloEn[i]);
        }
    }
    fclose(archivoEntrada);
}


char* escritura_Parcial(float * arregloCeldas, int cantidadCeldas,char * nombreSalida,char * iteracion){
	FILE * archivoSalida = fopen(nombreSalida, "w");
    //Se escribe el valor de energia de cada celda
    for (int i = 0; i < cantidadCeldas; i++)
    {
        fprintf(archivoSalida, "%d %f\n", i, arregloCeldas[i]);
    }
	fclose(archivoSalida);
  const char esp[2] = " ";
  char* salida = strcat(nombreSalida,esp);
  salida = strcat(salida,iteracion);

  return salida;
}

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

  int diferencia = superior - inferior;

  char* iteracion = "0";

  int cantidadParticulas = superior-inferior;

  float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
  
  int * arregloPos = (int*)malloc(cantidadParticulas*sizeof(int));
  
  int * arregloEn = (int*)malloc(cantidadParticulas*sizeof(int));  

  printf("previa lectura \n");

  lectura(arregloEn,arregloPos,nombreEntrada,inferior,superior);

  for(int i=0;i<diferencia;i++){
    printf("%d ",arregloEn[i]);
    printf(" %d \n",arregloPos[i]);
  }

  char* retorno;

  printf("post lectura \n");  

  bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas, cantidadParticulas,diferencia,nombre_salida,iteracion,retorno); 

  printf("salida : %s",retorno);
//	write(STDOUT_FILENO,retorno, 100); 

  free(arregloCeldas);
  free(arregloPos);
  free(arregloEn);

  return 0;

}


