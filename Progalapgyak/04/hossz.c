#include <stdio.h>

int hossz(char s[]) {
  int i;

  for (i = 0; s[i] != '\0'; ++i);

  return i;
}

int main() {
  char s[101];

  printf("Kerem a szoveget!\n");
  scanf("%[^\n]", s);

  printf("s=%s\n", s);

  printf("Az s hossza = %d\n", hossz(s));

  return 0;
}
