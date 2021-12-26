#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----DEFINICION DE FUNCIONES----

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

char * reune_Numeros(int anterior,int superior,int iteracion){

}


//Entrada: Nombre de un archivo como Char*
//Funcionamiento: Lee un archivo de entrada y guarda las energias de cada impacto   
//Salida: Arreglo de enteros 

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

//Entrada: Float x INT x INT x INT x INT
//Funcionamiento: Permite calcular el efecto del impacto de una particula en una celda especifica
//Salida: un flotante, que indica la energia resultante en la celda despues del impacto

float impacto(float energiaInicial, int energiaParticula, int cantidadCeldas, int posCelda, int posParticula){
    float newEnergia = energiaInicial + (1000*energiaParticula)/(cantidadCeldas*sqrtf((float)(abs(posParticula-posCelda) + 1)));
    return newEnergia;
}


//Entrada: Float* X INT* X INT * x INT X INT X CHAR*
//Funcionamiento: Calcula los efectos de cada bombardeo en las celdas y entrega un archivo de salida con los resultados finales
//Salida: Archivo de salida con el resultado final de las celdas

char* bombardeo(float * arregloCeldas, int * arregloPos, int * arregloEn, int cantidadCeldas, int cantidadParticulas,int diferencia,char * nombreSalida,char* iteracion){

    char* salida;
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

    return salida;

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

//Entrada: Float* X INT X CHAR* 
//Funcionamiento: Escribe un archivo de salida, con el formato de indicar en la primera fila la celda con mas energia
//Salida: Archivo TxT

void escritura_Final(float * arregloCeldas, int cantidadCeldas,char * nombreSalida){
	FILE * archivoSalida = fopen(nombreSalida, "w");
    int posMax = maximoPos(arregloCeldas, cantidadCeldas);
    //Se escribe la celda con mayor energia
    fprintf(archivoSalida, "%d %f\n", posMax, arregloCeldas[posMax]);

    //Se escribe el valor de energia de cada celda
    for (int i = 0; i < cantidadCeldas; i++)
    {
        fprintf(archivoSalida, "%d %f\n", i, arregloCeldas[i]);
    }
	fclose(archivoSalida);
}

//Entrada: Float* X INT
//Funcionamiento: Encuentra el valor maximo del arreglo de flotantes y entrega su posicion en el arreglo
//Salida: INT

int maximoPos(float * arregloCeldas, int cantidadCeldas){
    int posMax = 0;
    for (int i = 0; i < cantidadCeldas; i++)
    {
        if (arregloCeldas[posMax] < arregloCeldas[i])
        {
            posMax = i;
        }
    }
    return posMax;
}

int main(){
  return 0;
}
