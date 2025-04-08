#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "record.h"

void usage(const char*, int);
int readRecord(int, int, PRecord);

int
main(int argc, const char* argv[]) {

  if (argc != 3) {
    usage(argv[0], EXIT_FAILURE);
  }

  int id = atoi(argv[2]);

  if (id < 0 && id >= MAX_RECORDS) {
    usage(argv[0], EXIT_FAILURE);
  }
  
  int fd;
  fd = open(argv[1], O_RDONLY);
		    
  if (fd < 0) {
    fprintf(stderr, "Cannot create the file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  Record record;

  readRecord(fd, id, &record);
  printRecord(stdout, &record);

  close(fd);
  
  return EXIT_SUCCESS;
}

void
usage(const char* progname,
      int exitCode) {
  fprintf(stderr, "Usage: %s <filename> <id>\n", progname);
  fprintf(stderr, "\t\t<id> = [0, 1024)");
  _exit(exitCode);
}

int
readRecord(int fd, int id, PRecord data) {
  lseek(fd, id * sizeof(Record), SEEK_SET);
  return read(fd, data, sizeof(Record));
}
