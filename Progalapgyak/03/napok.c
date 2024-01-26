#include <stdio.h>

int main() {
  int nap_sorszam;

  printf("Kerem a nap sorszamat!\n");
  scanf("%d", &nap_sorszam);

  printf("nap=%d\n", nap_sorszam);

  switch (nap_sorszam) {
    case 1:
      printf("hetfo\n");
      break;
    case 2:
      printf("kedd\n");
      break;
    case 3:
      printf("szerda\n");
      break;
    case 4:
      printf("csutortok\n");
      break;
    case 5:
      printf("pentek\n");
      break;
    case 6:
      printf("szombat\n");
      break;
    case 7:
      printf("vasarnap\n");
      break;
    default:
      printf("rossz input!\n");
      break;
  }

  return 0;
}
