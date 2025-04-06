#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

int
main(int argc, char*argv[]) {

  if (argc != 2) {
    return 1;
  }

  int fd;
  fd = open(argv[1], O_CREAT, 0666);

  if (fd < 0) {
    fprintf(stderr, "No se pudo abrir el fichero");
    return 1;
  }

  close(fd);

  return 0;
}
