#include <stdio.h>

#define N 5

void feltolt(int t[]) {
  for (int i = 0; i < N; ++i) {
    scanf("%d", &t[i]);
  }
}

void kiir(int t[]) {
  printf("t=%p\n", t);
  printf("&t=%p\n", &t);

  int *p = t;

  for (int i = 0; i < N; ++i) {
    //printf("%d.: %d [%p]\n", i, t[i], &t[i]);
    // t[i] == i[t]
    //printf("%d.: %d [%p]\n", i, *(i + t), t + i);
    printf("%d.: %d [%p]\n", i, *p, p);

    ++p;
  }
}

int main() {
  int tomb[N];

  feltolt(tomb);
  kiir(tomb);

  return 0;
}