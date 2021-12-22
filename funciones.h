#ifndef FUNCIONESH
#define FUNCIONESH

void lecturaPos(int * arregloPos, char * nombreEntrada, int cantidadParticulas);
void lecturaEn(int * arregloEn, char * nombreEntrada, int cantidadParticulas);
float impacto(float energiaInicial, int energiaParticula, int cantidadCeldas, int posCelda, int posParticula);
void bombardeo(float * arregloCeldas, int * arregloPos, int * arregloEn, int cantidadCeldas, int cantidadParticulas,char * nombreSalida);
void escritura(float * arregloCeldas, int cantidadCeldas,char * nombreSalida);
int maximoPos(float * arregloCeldas, int cantidadCeldas);

#endif

