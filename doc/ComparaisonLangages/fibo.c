#include <stdio.h>
#include <time.h>

long fibo(long v) {
  if(v < 1) {
    return 1;
  } else {
    return fibo(v-1) + fibo(v-2);
  }
}

int main() {
  long t = 0;
  long res = 0;
  t = time(NULL);
  res = fibo(40);
  printf("%ld", res);
  printf("en %ld s", time(NULL) - t);
  return 0;
}
