/*Exemplo de como usar a biblioteca time.h*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main ()
{
  //Gets current time.
  time_t rawtime = time(0);
  struct tm * timeinfo;
  time ( &rawtime );

  timeinfo = localtime ( &rawtime);
  printf ( "Current local time and date: %s", asctime (timeinfo) );
  sleep(2);
  rawtime = time(NULL);
  timeinfo = localtime ( &rawtime);
  printf ( "Current local time and date: %s", asctime (timeinfo) );
  
  //Generates random numbers
  srand(time(NULL));
  int qtd, random;
  qtd = rand()%11;
  printf("%d Random numbers generated\n", qtd);
  while(qtd--){
    random = rand()%101;
    printf("%d\n", random);
  }
  return 0;
}