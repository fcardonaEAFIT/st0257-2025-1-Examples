#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_OPEN_FILE 1024

int
main(int argc, char*argv[]) {

  int fd[MAX_OPEN_FILE];
  extern int errno;
  for (int i = 0; i < MAX_OPEN_FILE; i++) {
    fd[i] = open("max_open_files.c", O_RDONLY);
    if (fd[i] < 0) {
      if (errno == EMFILE) {
	fprintf(stderr, "Se alcanzo la cuota maxima archivos abiertos %d\n", i);
      }
      else {
	fprintf(stderr, "No se pudo abrir el fichero\n");
      }
      return 1;
    }
  }
  

  for (int i = 0; i < MAX_OPEN_FILE; i++) {
    close(fd[i]);	
  }

  return 0;
}
