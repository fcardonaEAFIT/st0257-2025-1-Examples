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
  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    fprintf(stderr, "No se pudo abrir el fichero");
    return 1;
  }

  lseek(fd, 20, SEEK_CUR);
  
  char buffer[MAX_BUFFER_SIZE];

  int read_size;

  while ((read_size = read(fd, buffer, MAX_BUFFER_SIZE)) > 0) {
    write(1, buffer, read_size);
  }

  close(fd);

  return 0;
}
