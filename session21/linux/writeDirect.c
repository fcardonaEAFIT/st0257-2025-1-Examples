#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

void usage(const char*, int);
int writeRecord(int, const PRecord);

int
main(int argc, const char*argv[]) {

  if (argc != 5) {
    usage(argv[0], EXIT_FAILURE);
  }

  int id = atoi(argv[2]);

  if (id < 0 && id >= MAX_RECORDS) {
    usage(argv[0], EXIT_FAILURE);
  }

  const char* name = argv[3];
  double salary = atof(argv[4]);
  
  int fd;
  fd = open(argv[1], O_WRONLY);

  if (fd < 0) {
    fprintf(stderr, "Cannot open the file for writing %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  Record record;
  record.id = id;
  memcpy(record.name, name, sizeof(record.name));
  record.salary = salary;

  writeRecord(fd, &record);
  printRecord(stdout, &record);

  close(fd);
  return 0;
 
}

void
usage(const char* progname,
      int exitCode) {
  fprintf(stderr, "Usage: %s <filename> <id> <name> <salary>\n", progname);
  fprintf(stderr, "\t\t<id> = [0, 1024)\n");
  fprintf(stderr, "\t\t<name> A valid name until 50 characters\n");
  fprintf(stderr, "\t\t<salary>\n");
  _exit(exitCode);
}

int
writeRecord(int fd, const PRecord record) {
  lseek(fd, record->id * sizeof(Record), SEEK_SET);
  return write(fd, record, sizeof(Record));
}
