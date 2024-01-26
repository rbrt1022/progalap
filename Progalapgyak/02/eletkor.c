#include <stdio.h>

#define AKTUALIS_EV 2023

int main() {
  int szuletesi_ev;
  //int aktualis_ev = 2023;

  printf("Kerlek add meg a szuletesi eved!\n");
  scanf("%d", &szuletesi_ev);

  int eletkor = AKTUALIS_EV - szuletesi_ev;

  printf("A te eletkorod = %d\n", eletkor);

  return 0;
}