#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1


int main(int argc, char *argv[]) {



  char palabra[] = "Miguel_Mayorga Ivan_Tulilla Willy Laikita";

  const char s[2] = " ";
  char *token= strtok(argv[0], s);

  int i = 0;

  char migue[25];
  char chino[25];
  char laika[25];
  char willy[25]; 

  while( token != NULL ) {
      
      if(i == 0){
        strcpy(migue,token);
        printf( "%s\n", token );      
        i = i+1;    
      }
      else if(i == 1){
        strcpy(chino,token);
        printf( "%s\n", token );          
        i = i+1;    
      }
      else if(i == 2){
        strcpy(laika,token);
        printf( "%s\n", token );  
        i = i+1;    
      }
      else if(i == 3){
        printf( "%s\n", token );  
        strcpy(willy,token);
      } 

      token = strtok(NULL, s); 

     
  }

  printf("la perra:%s \n",migue);
  printf("niños %s %s \n",willy,laika);
  
  char* retorno = strcat(willy," en efecto, es la maquina");


	write(STDOUT_FILENO,retorno , 100);
	
	return 0;
}