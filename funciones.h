#ifndef FUNCIONESH
#define FUNCIONESH

//----------------Bloque de declaracion de funciones--------------------

float impacto(float energiaInicial, int energiaParticula, int cantidadCeldas, int posCelda, int posParticula);
void bombardeo(float * arregloCeldas, int * arregloPos, int * arregloEn, int cantidadCeldas, int diferencia,char * nombreSalida);
int maximoPos(float * arregloCeldas, int cantidadCeldas);
void lectura(int * arregloEn, int * arregloPos, char * nombreEntrada, int pos_inicial,int pos_final);
void escritura_Final(float * arregloCeldas, int cantidadCeldas,char * nombreSalida);
void escritura_Parcial(float * arregloCeldas, int cantidadCeldas,char * nombreSalida);
void asignar_Particulas(int particulas,int procesos,int n, int* arreglo_particulas);
int calcular_N(int particulas,int procesos);
int avance(int* arreglo,int posicion_final);



#endif

