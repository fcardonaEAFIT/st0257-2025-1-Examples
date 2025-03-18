#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* hilo(void*);

int
main(int argc, const char* argv[]) {

  const char *mensaje[] = { "Esta es una cadena que quiero separar",
    "Esta es otra cadena para el segundo hilo",
    "Esta es una t

  for (int i = 0; i < 3; i++) {
    pthread_create
  
  return 0;
}

int*
hilo(void* arg) {
  const char* mensaje = (char *) arg;
  
  char *cadena;

  cadena = malloc(strlen(mensaje) + 1);

  strcpy(cadena, mensaje);

  char* p = strtok(cadena, " ");

  while (p) {
    printf("%s\n", p);
    p = strtok(NULL, " ");
  }

  free(cadena);
  return 0;
}
  
