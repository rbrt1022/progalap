#include <stdio.h>

int main() {
  int szam;

  printf("Kerek egy egesz szamot!\n");
  scanf("%d", &szam);

  printf("szam=%d\n", szam);

  if (szam % 2 == 0) {
    printf("paros\n");
  } else {
    printf("paratlan\n");
  }

  //printf("par%s\n", (szam % 2 == 0) ? "os" : "atlan");

  if (szam > 0) {
    printf("pozitiv\n");
  } else if (szam < 0) {
    printf("negativ\n");
  } else {
    printf("NULLAAAA\n");
  }

  return 0;
}