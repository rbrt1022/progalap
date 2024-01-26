#include <stdio.h>

int main() {
  //int szam1, szam2, szam3, szam4, ...

  int tomb[10];

  for (int i = 0; i < 10; ++i) {
    tomb[i] = (i + 1) * (i + 1);
  }

  tomb[7] = -200;

  for (int i = -10; i < 15; ++i) {
    printf("tomb[%d]=%d\n", i, tomb[i]);
  }

  int tomb2[10] = {1, 3, 5, 7, 9};

  for (int i = 0; i < 10; ++i) {
    printf("tomb2[%d]=%d\n", i, tomb2[i]);
  }

  return 0;
}
