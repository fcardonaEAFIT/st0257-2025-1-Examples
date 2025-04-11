#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 16

/*
 * This program show the content of a file on the terminal using a sequential reading
 */

void usage(const char*, int);

int
main(int argc, const char *argv[]) {

  if (argc != 2) {
    usage(argv[0], EXIT_FAILURE);
  }

  int fd;
  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    fprintf(stderr, "No se pudo abrir el fichero");
    return 1;
  }

  char buffer[MAX_BUFFER_SIZE];

  int read_size;

  while ((read_size = read(fd, buffer, MAX_BUFFER_SIZE)) > 0) {
    write(1, buffer, read_size);
  }

  close(fd);

  return 0;
}

void
usage(const char *progname, int exitCode) {
  fprintf(stderr, "Usage: %s <filename>\n", progname);
  _exit(exitCode);
}
