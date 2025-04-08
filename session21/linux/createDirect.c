#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "record.h"

void usage(const char*, int);
int writeRecord(int, Record*);

int
main(int argc, char*argv[]) {

  if (argc != 2) {
    usage(argv[0], EXIT_FAILURE);
  }

  int fd;
  fd = creat(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if (fd < 0) {
    fprintf(stderr, "Cannot create the file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  double salary = 1200.0;
  for (int i = 0; i < MAX_RECORDS; i++) {
    Record data;
    data.id = i;
    sprintf(data.name, "A fake name: %d", i);
    data.salary = salary;
    salary += 300;
    writeRecord(fd, &data);
  }

  return EXIT_SUCCESS;
}

int
writeRecord(int fd, PRecord record) {
  return write(fd, record, sizeof(Record));
}

void
usage(const char* progname, int exitCode) {
  fprintf(stderr, "Usage: %s <filename>\n", progname);
  _exit(exitCode);
}
