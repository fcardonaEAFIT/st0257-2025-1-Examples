#include <stdio.h>
#include <windows.h>

#define SIZE 10

DWORD WINAPI thr_1(LPVOID);
DWORD WINAPI thr_2(LPVOID);

int
main() {
  // pthread_t thr1, thr2;
  HANDLE htr1, htr2;
  int *arg_1;
  int *arg_2;

  arg_1 = malloc(sizeof(int) *SIZE);
  arg_2 = malloc(sizeof(int) *SIZE);

  /* pthread_create(&thr1, NULL, thr_1, (void *) arg_1); */
  /* pthread_create(&thr2, NULL, thr_2, (void *) arg_2); */

  htr1 = CreateThread(NULL, 0, thr_1, (LPVOID) arg_1);

  if (htr1 == INVALID_HANDLE) {
    fprint(stderr, "Error: %d \n", GetLastError());
    exit(1);
  }

  htr1 = CreateThread(NULL, 0, thr_2, (LPVOID) arg_2);

  int *ret_value_thr1;
  int *ret_value_thr2;

  // pthread_join(thr1, (void *) &ret_value_thr1);
  // pthread_join(thr2, (void *) &ret_value_thr2);
  ret_value_thr1 = (int*) WaitForSingleObject(htr1, 0);
  ret_value_thr2 = (int*) WaitForSingleObject(htr2, 0);

  printf("thr1 return value: %d\n", *ret_value_thr1);
  for (int i = 0; i < SIZE; i++) {
    printf("arr[%d]=%d\n", i, *(arg_1 + i));
  }

  free(arg_1);
  free(ret_value_thr1);

  printf("thr2 return value: %d\n", *ret_value_thr2);
  for (int i = 0; i < SIZE; i++) {
    printf("arr[%d]=%d\n", i, arg_2[i]);
  }

 free(arg_2);
 free(ret_value_thr2);
  _exit(0);
}

DWORD WINAPI
thr_1(LPVOID arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 1;
  }

  int *x = (int*) malloc(sizeof(int));
  *x = 1;

  return (void *) x;
}

DWORD WINAPI
thr_2(LPVOID arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 2;
  }

  int *x = (int*) malloc(sizeof(int));
  *x = 2;

  return (void *) x;
}
