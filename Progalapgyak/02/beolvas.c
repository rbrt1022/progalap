#include <stdio.h>

int main() {
  int szam;
  double valos;

  printf("Kerek egy egesz es egy valos szamot!\n");
  scanf("%d %lf", &szam, &valos);

  printf("szam=%d\nvalos=%lf\n", szam, valos);
  
  return 0;
}