#include <stdio.h>
#include <stdlib.h>


typedef int egesz;
//typedef unsigned long long uint64_t;

typedef struct {
  int dmg;
  float crit;
} fegyver_t;

typedef struct {
  char nev[50];
  egesz hp;
  fegyver_t fegyver;
} karakter_t;

fegyver_t fegyver_beolvas() {
  fegyver_t f;

  printf("Kerem a dmg-t!\n");
  scanf("%d", &f.dmg);

  printf("Kerem a crit-et!\n");
  scanf("%f", &f.crit);

  return f;
}

karakter_t karakter_beolvas() {
  karakter_t k;

  printf("Kerem a karakter nevet!\n");
  scanf("%s", k.nev);

  printf("Kerem a karakter hp-ját!\n");
  scanf("%d", &k.hp);

  k.fegyver = fegyver_beolvas();

  return k;
}

void harc(karakter_t k1, karakter_t k2) {
  
}

int main() {
  karakter_t karakterek[3];

  for (int i = 0; i < 3; ++i) {
    karakterek[i] = karakter_beolvas();
  }

  for (int i = 0; i < 3 - 1; ++i) {
    harc(karakterek[i], karakterek[i + 1]);
  }


  return 0;
}