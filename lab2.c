//----LIBRERIAS----
#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <sys/wait.h> 
#include <sys/types.h> 

#define LECTURA 0
#define ESCRITURA 1

extern void niceprint(int N, float *Energy, float Maximum);

//Autor: Nicolas Torreblanca

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
    int n  = calcular_N(cantidadParticulas,cantidadProcesos);
    int * arreglo = (int*)malloc(n*sizeof(int));

    asignar_Particulas(cantidadParticulas,cantidadProcesos,n,arreglo);
  

    int status;

    int proceso_hijo = 0;
    int proceso_padre = 0;

    int posterior = 0;
    int anterior = 0;
    int pid1 = -1;


    for(int i = 0; i < n; i ++){
      int * pipesPH = (int*)malloc(sizeof(int)*2); 
      int * pipesHP = (int*)malloc(sizeof(int)*2);
      char aux[125];

      pipe(pipesPH);
      pipe(pipesHP);

      pid1 = fork();

      if (pid1 == -1)
      {       
          break;
      }

      if (pid1 == 0)
      {
          //Se entra en el proceso hijo

          proceso_hijo = proceso_hijo +1;

          close(pipesPH[ESCRITURA]);
          close(pipesHP[LECTURA]);
          read(pipesPH[LECTURA],aux,sizeof(aux));

          //Se crea el String con parametros para el exec

          char* esp = " ";        
          char buffPH[125];

          char celdas[12];
          sprintf(celdas, "%d", cantidadCeldas);

          strcpy(buffPH,nombreEntrada);
          strcat(buffPH,esp);
          strcat(buffPH,nombreSalida);
          strcat(buffPH,esp);
          strcat(buffPH,celdas);
          strcat(buffPH,esp);
          strcat(buffPH,aux);
        
          char *args[2]={buffPH,NULL};

          printf("Se entrego :%s \n",args[0]);

          dup2(pipesHP[ESCRITURA],STDOUT_FILENO);
          execvp("./bomb",args);

          printf(" exec fallo \n");
          perror("exec ls failed");
          exit(EXIT_FAILURE);

          free(pipesHP);
          break;

      }else{
          proceso_padre = proceso_padre + 1;

          char bufferHP[100];      

          posterior = avance(arreglo,i+1);
          anterior = avance(arreglo,i);

                
          char ant_str[12];
          sprintf(ant_str, "%d", anterior);
          char post_str[12];
          sprintf(post_str, "%d", posterior);
          char iter[12];
          sprintf(iter, "%d",i);
          char* esp = " ";
          char* aux = strcat(ant_str,esp);
          aux = strcat(aux,post_str);
          aux = strcat(aux,esp);
          aux = strcat(aux,iter);  

          close(pipesPH[LECTURA]);
          close(pipesHP[ESCRITURA]);
          
          write(pipesPH[ESCRITURA], aux,sizeof(aux));

          wait(&status);
          
          read(pipesHP[LECTURA], bufferHP, 100);

          printf("Mi hijo escribio: %s\n", bufferHP);
  
          int auxiliarPos;
          float* futuro = (float*)malloc(cantidadCeldas* sizeof(float));

          const char s[2] = " ";
          char*inicial = strtok(bufferHP,s);
          int i = 0;
          char nombreEntrada[25];
          char iters[25];

          while( inicial != NULL ) {
              
              if(i == 0){
                strcpy(nombreEntrada,inicial);   
                i = i+1;    
              }
              else if(i == 1){
                strcpy(iters,inicial);    
                i = i+1;    
              }
              inicial = strtok(NULL, s);   
            }

            int iteracion = atoi(iters);



            //Lectura del archivo
            FILE * archivoEntrada = fopen(nombreEntrada, "r");
            if (archivoEntrada == NULL)
            {
                perror("\nArchivo No Existente\n");
            }else{
                for (int i = 0; i < cantidadCeldas; i++)
                  {
                      fscanf(archivoEntrada, "%d", &auxiliarPos);
                      fscanf(archivoEntrada, "%f", &futuro[i]);
                      
                  }
              fclose(archivoEntrada);
            }

            for(int j = 0; j < cantidadCeldas;j++){
                arregloCeldas[j] = arregloCeldas[j] + futuro[j];
            }

            free(futuro);

            if(iteracion+1 == n){
              escritura_Final(arregloCeldas,cantidadCeldas,nombreSalida);
            }
                
            free(pipesPH);
          }
          printf("\nPP : %d , PH : %d\n",proceso_padre,proceso_hijo);
        }


        
        //Se calculo la celda con mayor energia
        int posMax = maximoPos(arregloCeldas, cantidadCeldas);

        //Se utiliza la funcion niceprint si la bandera -D es utilizada en el comando de ejecucion
        if(bandera == 1){
            niceprint(cantidadCeldas, arregloCeldas, arregloCeldas[posMax]);
        }

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
