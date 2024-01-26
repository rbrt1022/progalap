#include <stdio.h>

int main() {
  int szam;

  printf("Kerek egy egesz szamot!\n");
  scanf("%d", &szam);

  printf("szam=%d\n", szam);

  int i = 1;
  int osszeg = 0;

  while (i <= szam) {
    printf("i=%d\n", i);

    osszeg += i;

    i++;
  }

  printf("osszeg=%d\n", osszeg);

  return 0;
}
