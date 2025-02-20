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

  // arg_1 = malloc(sizeof(int) *SIZE);
  // arg_2 = malloc(sizeof(int) *SIZE);
  arg_1 = (int*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(int) * SIZE);
  arg_2 = (int*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(int) * SIZE);

  hthr1 = CreateThread(NULL, 0, thr_1, (LPVOID) arg_1, 0, &thrId1);

  if (hthr1 == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Error: %d \n", GetLastError());
    exit(1);
  }

  hthr2 = CreateThread(NULL, 0, thr_2, (LPVOID) arg_2, 0, &thrId2);

  if (hthr2 == INVALID_HANDLE_VALUE) {
    fprintf(stderr, "Error: %d \n", GetLastError());
    exit(1);
  }
  
  WaitForSingleObject(hthr1, INFINITE);
  WaitForSingleObject(hthr2, INFINITE);

  DWORD ret_value_thr1;
  DWORD ret_value_thr2;
  GetExitCodeThread(hthr1, &ret_value_thr1);
  GetExitCodeThread(hthr2, &ret_value_thr2);
  
  printf("thr1 return value: %d\n", ret_value_thr1);
  for (int i = 0; i < SIZE; i++) {
    printf("arg_1[%d]=%d\n", i, arg_1[i]);
  }

  printf("thr2 return value: %d\n", ret_value_thr2);
  for (int i = 0; i < SIZE; i++) {
    printf("arg_2[%d]=%d\n", i, arg_2[i]);
  }

  HeapFree(GetProcessHeap(), 0, arg_1);
  HeapFree(GetProcessHeap(), 0, arg_2);

  CloseHandle(hthr1);
  CloseHandle(hthr2);

  ExitProcess(0);
}

DWORD WINAPI
thr_1(LPVOID arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 1;
  }

  ExitThread(1);
}

DWORD WINAPI
thr_2(LPVOID arg) {
  int *arr = (int *) arg;

  for (int i = 0; i < SIZE; i++) {
    arr[i] = 2;
  }

  ExitThread(2);
}
