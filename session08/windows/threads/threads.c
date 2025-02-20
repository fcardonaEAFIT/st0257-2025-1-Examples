#include <stdio.h>
#include <windows.h>

#define SIZE 10

DWORD WINAPI thr_1(LPVOID);
DWORD WINAPI thr_2(LPVOID);

int
main() {
  HANDLE hthr1, hthr2;
  DWORD  thrId1, thrId2;
  
  int *arg_1;
  int *arg_2;

  arg_1 = malloc(sizeof(int) *SIZE);
  arg_2 = malloc(sizeof(int) *SIZE);

  hthr1 = CreateThread(NULL, 0, thr_1, (LPVOID) arg_1, 0, &thrId1);

  if (hthr1 == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Error: %d \n", GetLastError());
    exit(1);
  }

  hthr2 = CreateThread(NULL, 0, thr_2, (LPVOID) arg_2, 0, &thrId2);

  int *ret_value_thr1;
  int *ret_value_thr2;

  if (hthr2 == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Error: %d \n", GetLastError());
    exit(1);
  }
  
  fprintf(stdout, "Waiting for thread to end\n");
  WaitForSingleObject(hthr1, 0);
  WaitForSingleObject(hthr2, 0);

  fprintf(stdout, "Threads has ended\n");
  GetExitCodeThread(hthr1, (LPDWORD) &ret_value_thr1);
  GetExitCodeThread(hthr2, (LPDWORD) &ret_value_thr2);
  
  printf("thr1 return value: %d\n", *ret_value_thr1);
  for (int i = 0; i < SIZE; i++) {
    fprintf(stderr, "arr[%d]=%d\n", i, *(arg_1 + i));
  }

  free(arg_1);
  free(ret_value_thr1);

  printf("thr2 return value: %d\n", *ret_value_thr2);
  for (int i = 0; i < SIZE; i++) {
    fprintf(stderr, "arr[%d]=%d\n", i, arg_2[i]);
  }

 free(arg_2);
 free(ret_value_thr2);

 CloseHandle(hthr1);
 CloseHandle(hthr2);

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

  ExitThread((DWORD) x);
}

DWORD WINAPI
thr_2(LPVOID arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 2;
  }

  int *x = (int*) malloc(sizeof(int));
  *x = 2;
  
  ExitThread((DWORD) x);
}
