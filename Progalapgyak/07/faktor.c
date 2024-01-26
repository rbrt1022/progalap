#include <stdio.h>


int fakt(int n) {
  printf("fakt(%d)\n", n);

  if (n <= 0) {
    return 1;
  } else {
    int f = n * fakt(n - 1);

    return f;
  }
}

int main() {
  int szam;
  scanf("%d", &szam);

  printf("%d!=%d\n", szam, fakt(szam));

  return 0;
}