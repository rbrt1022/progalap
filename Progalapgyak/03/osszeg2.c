#include <stdio.h>

int main() {
  int szam;
  int osszeg = 0;

  do {
    printf("Kerek egy egesz szamot!\n");
    scanf("%d", &szam);

    printf("szam=%d\n", szam);

    osszeg += szam;
  } while (szam != 0);

  printf("osszeg=%d\n", osszeg);

  return 0;
}
