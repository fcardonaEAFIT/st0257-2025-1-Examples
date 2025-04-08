#include "record.h"

void
printRecord(FILE* stream, const PRecord record) {
  fprintf(stream, "Id: %d Name: %s Salary: %f\n",
	  record->id,
	  record->name,
	  record->salary);
}
