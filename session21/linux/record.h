#include <stdio.h>
#define MAX_NAME 50
#define MAX_RECORDS 1024

struct record {
  int id;
  char name[MAX_NAME];
  double salary;
};

typedef struct record Record;
typedef struct record* PRecord;

void printRecord(FILE* stream, PRecord record);
