//----LIBRERIAS----
#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern void niceprint(int N, float *Energy, float Maximum);

//Autores: Nicolas Torreblanca y Rodrigo Escobar

int main(int argc, char ** argv){
    //Declaracion de variables para calculo de tiempo de ejecucion
    clock_t tiempo_inicio;
    clock_t tiempo_final;
    double segundos;
    
    //Se guarda el tiempo de inicio de ejecucion
    tiempo_inicio = clock();

    //Declaracion de variables para lectura de archivos
    char * nombreEntrada = NULL;
    char * nombreSalida = NULL;
    int cantidadCeldas;
    int cantidadProcesos;
    //cantidadLineas = cantidadParticulas
    int cantidadParticulas;
    int bandera = 0;

    //El siguiente ciclo se utiliza para recibir los parametros de entrada usando getopt
    // N = cantidadCeldas
    // p = cantidadProcesos
    // c = cantidadParticulas = cantidadLineas
    // i = archivoEntrada
    // o = archivoSalida
    // D = bandera grafico
    int z;
    while ((z = getopt (argc, argv, "N:p:c:i:o:D")) != -1)
    {
        switch (z)
        {
        case 'N':
            sscanf(optarg, "%d", &cantidadCeldas);
            printf("cantidadCeldas: %d\n", cantidadCeldas);
            break;
        case 'p':
            sscanf(optarg, "%d", &cantidadProcesos);
            printf("cantidadProcesos: %d\n", cantidadProcesos);
            break;
        case 'c':
            sscanf(optarg, "%d", &cantidadParticulas);
            printf("cantidadParticulas: %d\n", cantidadParticulas);
            break;    
        case 'i':
            nombreEntrada = optarg;
            break;
        case 'o':
            nombreSalida = optarg;
            break;
        case 'D':
            bandera = 1;
            break;
        case '?':
            if (optopt == 'N'){
                fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }else if (optopt == 'p'){
                fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }else if (optopt == 'c'){
                fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }else if (optopt == 'i'){
                fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }else if (optopt == 'o'){
                fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            }else if (isprint(optopt))
            {
                fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
            }else{
                fprintf (stderr,
                "Opcion con caracter desconocido `\\x%x'.\n",
                optopt);
            }
            return 1;
        default:
            abort ();
        }
    }
    //Se obtiene la cantidad de particulas en el archivo de entrada
    //int cantidadParticulas = lecturaCan(nombreEntrada);

    //Se reserva memoria para los arreglos dinamicos
    float * arregloCeldas = (float*)malloc(cantidadCeldas*sizeof(float));
    int * arregloPos = (int*)malloc(cantidadParticulas*sizeof(int));
    int * arregloEn = (int*)malloc(cantidadParticulas*sizeof(int));

    //Estos arreglos se rellenan con la lectura del archivo de entrada
    lecturaPos(arregloPos, nombreEntrada, cantidadParticulas);
    //printf("PRIMER CP\n");
    lecturaEn(arregloEn, nombreEntrada, cantidadParticulas);
    //printf("SEGUNDO CP\n");

    //------ PROBLEMAS QUE RESOLVER ------
    //cantidadProcesos = cantidad de procesos hijos que se deben generar

    //  CANTIDAD DE PARTICULAS POR PROCESO HIJO
    // particulaPorProceso = cantidadParticulas/cantidadProcesos
    
    //  GENERAR PROCESOS HIJOS (fork)

    //  PIPES BIDIRECCIONALES
    // - PADRE ESCRIBE, HIJO LEE - 
    //      PROCESO HIJO CALCULA IMPACTO
    // - HIJO ESCRIBE, PADRE LEE -

    //  CANTIDAD DE PARTICULAS POR PROCESO HIJO
    // particulaPorProceso = cantidadParticulas/cantidadProcesos

    //------ ORDEN ------
    // 1 HIJOS RECIBEN PARAMETROS POR PIPES
    // 2 HIJOS CALCULAN PARCIALMENTE ACUMULACION DE ENERGIA
    // 3 HIJO ESCRIBE RESULTADO DE CALCULO A PADRE MEDIANTE PIPES
    // 4 PADRE LEE TODOS LOS RESULTADOS DE HIJOS
    // 5 PADRE SUMA TODOS LOS RESULTADOS


    //Ejecucion de la funcion bombardeo
    bombardeo(arregloCeldas, arregloPos, arregloEn, cantidadCeldas, cantidadParticulas, nombreSalida);
    //printf("TERCER CP\n");
  
    //Se calculo la celda con mayor energia
    int posMax = maximoPos(arregloCeldas, cantidadCeldas);
    //printf("CUARTO CP\n");

    //Se utiliza la funcion niceprint si la bandera -D es utilizada en el comando de ejecucion
    if(bandera == 1){
        niceprint(cantidadCeldas, arregloCeldas, arregloCeldas[posMax]);
    }
    //printf("QUINTO CP\n");
  
    //Liberacion de memoria
    free(arregloCeldas);
    free(arregloPos);
    free(arregloEn);

    //Se obtiene el tiempo al momento del termino de ejecucion
    tiempo_final = clock();
    segundos = (double)(tiempo_final - tiempo_inicio)/CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %f\n", segundos);
    return 0;
}
