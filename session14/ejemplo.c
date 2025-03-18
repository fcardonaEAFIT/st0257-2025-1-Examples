#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* hilo(void*);

int
main(int argc, const char* argv[]) {

  const char * mensaje[] = { "Esta es una cadena que quiero separar",
	  "Esta es la segunda linea",
	  "Esta es la tercera linea" };

  pthread_t hilos[3];
  for (int i = 0; i < 3; i++) {
	 pthread_create(&hilos[i],
			 NULL,
			 hilo,
			 (void *) mensaje[i]);
  }


  return 0;
}

void*
hilo(void *arg) {
  char *cadena;
  char *mensaje = (char *) arg;

  cadena = malloc(strlen(mensaje) + 1);
  char *savespace = malloc(1000);

  strcpy(cadena, mensaje);

  char* p = strtok_r(cadena, " ", &savespace);

  while (p) {
    printf("%s\n", p);
    p = strtok_r(NULL, " ", &savespace);
  }

  free(cadena);
  return 0;
}
