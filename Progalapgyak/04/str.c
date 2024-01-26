#include <stdio.h>

int main() {
  char szoveg[10];

  szoveg[5] = 'X';

  for (int i = 0; i < 10; ++i) {
    printf("szoveg[%d]=%c %d\n", i, szoveg[i], szoveg[i]);
  }

  char sz2[] = {'A', 'B', 'C'};

  for (int i = 0; i < 3; ++i) {
    printf("sz2[%d]=%c\n", i, sz2[i]);
  }

  sz2[2] = 0;
  sz2[2] = '\0';

  printf("szoveg='%s'\n", szoveg);
  printf("sz2='%s'\n", sz2);

  return 0;
}