#include <stdio.h>

float kerulet(float a, float b);
float terulet(float a, float b);

void teglalap_szamol() {
  float a, b;

  printf("Kerem a teglalap ket oldalat!\n");
  scanf("%f %f", &a, &b);

  printf("tsz a=%f b=%f\n", a, b);

  float ker = kerulet(a, b);

  printf("tsz a=%f b=%f\n", a, b);
  float ter = terulet(a, b);

  printf("kerulet=%f\nterulet=%f\n", ker, ter);
}

int main() {
  teglalap_szamol();

  return 0;
}

float kerulet(float a, float b) {
  printf("ker a=%f b=%f\n", a, b);

  float ker = 2 * (a + b);

  a *= 10;

  printf("ker a=%f b=%f\n", a, b);
  return ker;
}

float terulet(float a, float b) {
  return a * b;
}

