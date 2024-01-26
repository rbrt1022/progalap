#include <stdio.h>
#include <stdlib.h>

void megfordit(char *s) {
  char *eleje, *vege;

  eleje = s;

  for (vege = eleje; *vege != '\0'; ++vege) {
    printf("[%p] %c\n", vege, *vege);
  }

  --vege;

  printf("[%p] %c\n", vege, *vege);

  for (; eleje < vege; ++eleje, --vege) {
    char tmp = *eleje;
    *eleje = *vege;
    *vege = tmp;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  printf("n=%d\n", n);

  char *str = (char*)malloc(sizeof(char) * n);

  scanf("%s", str);

  printf("elotte=%s\n", str);
  megfordit(str);
  printf("utana=%s\n", str);

  free(str);

  return 0;
}