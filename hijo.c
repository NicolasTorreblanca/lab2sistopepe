#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1


int main(int argc, char *argv[]) {

  const char s[2] = " ";
  char *token;
   
   /* get the first token */
  token = strtok(argv[0], s);
   
   /* walk through other tokens */
  while( token != NULL ) {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
  }

//  char* retorno = strcat(argv[0]," en efecto, son las maquinas");


//	write(STDOUT_FILENO,retorno , 100);
	
	return 0;
}