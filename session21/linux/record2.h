#define MAX_NAME 50

struct Index {
  int id;
  long nrecord;
};

struct Record {
  int id;
  char name[MAX_NAME];
  double salary;
};
	   
