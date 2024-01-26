#include <stdio.h>

#define N 6

void beolvas(int tomb[]) {
  for (int i = 0; i < N; ++i) {
    printf("Kerek egy egesz szamot!\n");
    scanf("%d", &tomb[i]);
  }
}

void kiir(int tomb[]) {
  for (int i = 0; i < N; ++i) {
    printf("tomb[%d]=%d\n", i, tomb[i]);
  }
}

float atlag(int t[]) {
  int osszeg = 0;

  for (int i = 0; i < N; ++i) {
    osszeg += t[i];
  }

  float eredmeny = osszeg / (float) N;

  return eredmeny;
}

void megfordit(int t[]) {
  /*for (int i = N - 1; i >= 0; --i) {
    printf("tomb[%d]=%d\n", i, t[i]);
  }*/

  for (int i = 0, j = N - 1; i < j; ++i, --j) {
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
  }
}

int main() {
  int szamok[N];

  beolvas(szamok);
  kiir(szamok);

  printf("atlag=%f\n", atlag(szamok));

  megfordit(szamok);

  kiir(szamok);

  return 0;
}
