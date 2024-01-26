#include <stdio.h>

int main() {
  FILE* be;
  be = fopen("input.txt", "r");

  // stdin
  // stdout
  // stderr
  // scanf("%f", &valt);
  // fscanf(stdin, "%f", &valt);

  if (be == NULL) {
    fprintf(stderr, "Nem sikerült megnyiti az input.txt fájlt!\n");
    return -1;
  }

  int szam;
  if (fscanf(be, "%d", &szam) != 1) {
    printf("Nem sikerült beolvasni a szamot!\n");
    return -2;
  }

  FILE* ki;
  ki = fopen("output.txt", "w");

  if (ki == NULL) {
    printf("Nem sikerült megnyiti az output.txt fájlt!\n");
    return -3;
  }

  if (fprintf(ki, "%d\n", szam * 2) == 0) {
    printf("Nem sikerült kiirni!\n");
    return -4;
  }

  fclose(be);
  fclose(ki);

  return 0;
}