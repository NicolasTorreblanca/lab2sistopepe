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
            break;
        case 'p':
            sscanf(optarg, "%d", &cantidadProcesos);
            break;
        case 'c':
            sscanf(optarg, "%d", &cantidadParticulas);
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

    //Se calcula la cantidad de hijos que se tienen que generar

    int n  = calcular_N(cantidadParticulas,cantidadProcesos);
    int * arreglo = (int*)malloc(n*sizeof(int));

    //Se le asigna a cada hijo una cantidad de particulas

    asignar_Particulas(cantidadParticulas,cantidadProcesos,n,arreglo);
  

    int status;
    int proceso_hijo = 0;
    int proceso_padre = 1;
    int posterior = 0;
    int anterior = 0;
    int escrito = 0;
    int pid1 = -1;


    for(int i = 0; i < n; i ++){
      int * pipesPH = (int*)malloc(sizeof(int)*2); 
      int * pipesHP = (int*)malloc(sizeof(int)*2);
      char aux[125];

      //Se declaran 2 pipes
      //Uno es de padre Hijo, donde el padre escribe y el hijo Lee
      //El otro es un Pipe donde el hijo escribe y el padre Lee

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

          proceso_padre = proceso_padre +1;

          close(pipesPH[ESCRITURA]);
          close(pipesHP[LECTURA]);

          //Se reciben los parametros del padre a traves del pipe

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


          //Se ingresa al exec con el string que posee 
          //los parametros de entrada para el funcionamiento

          dup2(pipesHP[ESCRITURA],STDOUT_FILENO);
          execvp("./bomb",args);

          //Se escribe lo que se obtiene en el padre

          printf(" exec fallo \n");
          perror("exec ls failed");
          exit(EXIT_FAILURE);

          //Se libera el pipe

          free(pipesHP);
          break;

      }else{
          //Proceso padre
          proceso_hijo = proceso_hijo + 1;
          char bufferHP[100];      

          //Primero se calcula en donde tiene que trabajar el hijo

          posterior = avance(arreglo,i+1);
          anterior = avance(arreglo,i);

          //Se escribe un string que sirven de parametros para el hijo

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

          //Se comunica al hijo mediante un pipe los parametros
          
          write(pipesPH[ESCRITURA], aux,sizeof(aux));

          wait(&status);
          
          read(pipesHP[LECTURA], bufferHP, 100);

          //Se pasa a traves del pipe
          //El padre lee lo que el hijo escribe

          printf("Mi hijo escribio: %s\n", bufferHP);
  
          int auxiliarPos;
          float* futuro = (float*)malloc(cantidadCeldas* sizeof(float));

          //Se procesa el string que se recibe

          const char s[2] = " ";
          char*inicial = strtok(bufferHP,s);
          int i = 0;
          char archivoEscrito[25];
          char iters[25];
        
          while( inicial != NULL ) {
              
              if(i == 0){
                strcpy(archivoEscrito,inicial);   
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
            //Se busca leer lo que escribio el archivo hijo

            FILE * archivoEntrante = fopen(archivoEscrito, "r");
            if (archivoEntrante == NULL)
            {
                perror("\nArchivo No Existente\n");
            }else{
                for (int i = 0; i < cantidadCeldas; i++)
                  {
                      fscanf(archivoEntrante, "%d", &auxiliarPos);
                      fscanf(archivoEntrante, "%f", &futuro[i]);
                      
                  }
              fclose(archivoEntrante);
            }

            //Se suma lo escrito por el hijo a lo escrito por los demas hijos

            for(int j = 0; j < cantidadCeldas;j++){
                arregloCeldas[j] = arregloCeldas[j] + futuro[j];
            }

            free(futuro);

            //Si se llega al final de la iteracion, se escribe el archivo de salida

            if(iteracion+1 == n){
              escritura_Final(arregloCeldas,cantidadCeldas,nombreSalida);
              escrito = 1;
            }
                
            free(pipesPH);
          }
          printf("\nProcesos hijo : %d , Procesos padre : %d\n",proceso_hijo,proceso_padre);
        }


        
        //Se calculo la celda con mayor energia
        int posMax = maximoPos(arregloCeldas, cantidadCeldas);

        //Se utiliza la funcion niceprint si la bandera -D es utilizada en el comando de ejecucion
        if(bandera == 1){
            niceprint(cantidadCeldas, arregloCeldas, arregloCeldas[posMax]);
        }

        //En caso de no existir una salida, se escribe una

        if(escrito != 1){
          escritura_Final(arregloCeldas,cantidadCeldas,nombreSalida);
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
