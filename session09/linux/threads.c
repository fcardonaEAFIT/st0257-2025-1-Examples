#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1000

void* thr_1(void *);
void* thr_2(void *);

int
main() {
  pthread_t thr1, thr2;
  int *arg_1;
  int *arg_2;

  arg_2 = arg_1 = malloc(sizeof(int) *SIZE);
  // arg_2 = malloc(sizeof(int) *SIZE);

  pthread_create(&thr1, NULL, thr_1, (void *) arg_1);
  pthread_create(&thr2, NULL, thr_2, (void *) arg_2);

  int *ret_value_thr1;
  int *ret_value_thr2;

  pthread_join(thr1, (void *) &ret_value_thr1);
  pthread_join(thr2, (void *) &ret_value_thr2);

  printf("thr1 return value: %d\n", *ret_value_thr1);
  for (int i = 0; i < SIZE; i++) {
    printf("arr_1[%d]=%d\n", i, *(arg_1 + i));
  }

  free(arg_1);
  free(ret_value_thr1);

  printf("thr2 return value: %d\n", *ret_value_thr2);
  for (int i = 0; i < SIZE; i++) {
    printf("arr_2[%d]=%d\n", i, arg_2[i]);
  }
 
  // free(arg_2);
 free(ret_value_thr2);
  _exit(0);
}

void*
thr_1(void * arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 1;
  }

  int *x = (int*) malloc(sizeof(int));
  *x = 1;

  return (void *) x;
}

void*
thr_2(void * arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 2;
  }

  int *x = (int*) malloc(sizeof(int));
  *x = 2;

  return (void *) x;
}

