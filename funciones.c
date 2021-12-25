#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//----DEFINICION DE FUNCIONES----

//Entrada: Nombre de un archivo como Char*
//Funcionamiento: Lee un archivo de entrada y guarda en un arreglo las posiciones de impacto
//Salida:  Arreglo de enteros

void lecturaPos(int * arregloPos, char * nombreEntrada, int cantidadParticulas){    
    int auxiliarEnergia;

    //Lectura del archivo
    FILE * archivoEntrada = fopen(nombreEntrada, "r");
    if (archivoEntrada == NULL)
    {
        perror("\nArchivo No Existente\n");
    }else{
        //fscanf(archivoEntrada, "%d", &cantidadParticulas);
        for (int i = 0; i < cantidadParticulas; i++)
        {
            fscanf(archivoEntrada, "%d", &arregloPos[i]);
            fscanf(archivoEntrada, "%d", &auxiliarEnergia);
        }
    }
    fclose(archivoEntrada);
}

//Entrada: Nombre de un archivo como Char*
//Funcionamiento: Lee un archivo de entrada y guarda las energias de cada impacto   
//Salida: Arreglo de enteros 

void lecturaEn(int * arregloEn, char * nombreEntrada, int cantidadParticulas){
    int auxiliarPos;

    //Lectura del archivo
    FILE * archivoEntrada = fopen(nombreEntrada, "r");
    if (archivoEntrada == NULL)
    {
        perror("\nArchivo No Existente\n");
    }else{
        //fscanf(archivoEntrada, "%d", &cantidadParticulas);
        for (int i = 0; i < cantidadParticulas; i++)
        {
            fscanf(archivoEntrada, "%d", &auxiliarPos);
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

void bombardeo(float * arregloCeldas, int * arregloPos, int * arregloEn, int cantidadCeldas, int cantidadParticulas,char * nombreSalida){
    float energiaInicial;
    float newEnergia;
    for (int i = 0; i < cantidadParticulas; i++)
    {
        for (int j = 0; j < cantidadCeldas; j+  +)
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
    escritura(arregloCeldas, cantidadCeldas, nombreSalida);
}

//Entrada: Float* X INT X CHAR* 
//Funcionamiento: Escribe un archivo de salida, con el formato de indicar en la primera fila la celda con mas energia
//Salida: Archivo TxT

void escritura(float * arregloCeldas, int cantidadCeldas,char * nombreSalida){
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
/*
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
*/