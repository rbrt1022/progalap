#include <stdio.h>

#define ESZAK 0
#define KELET 1
#define DEL 2
#define NYUGAT 3

typedef struct {
  int irany;
  int x, y;
} battya;

void balra(battya* b) {
  b->irany--;

  if (b->irany < 0) {
    b->irany = NYUGAT;
  }
}

void jobbra(battya* b) {
  b->irany++;

  if (b->irany > NYUGAT) {
    b->irany = ESZAK;
  }
}

void elore(battya* b, int mennyit) {
  switch (b->irany) {
    case ESZAK:
      b->y += mennyit;
      break;
    case KELET:
      b->x += mennyit;
      break;
    case DEL:
      b->y -= mennyit;
      break;
    case NYUGAT:
      b->x -= mennyit;
      break;
    default:
      break;
  }
}

int csinal(char s[]) {
  battya b = {.irany = ESZAK, .x = 0, .y = 0};
  int mennyit = 0;

  for (int i = 0; s[i] != '\0'; ++i) {
    switch (s[i]) {
      case 'b':
        balra(&b);
        break;
      case 'j':
        jobbra(&b);
        break;
      case 'e':
        b.irany = ESZAK;
        break;
      case 'k':
        b.irany = KELET;
        break;
      case 'd':
        b.irany = DEL;
        break;
      case 'n':
        b.irany = NYUGAT;
        break;
      /*case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':*/
      case '0'...'9':
        mennyit = s[i] - '0';
        elore(&b, mennyit);
        break;
      default:
        break;
    }
  }

  return b.x + b.y;
}

int main() {
  FILE* be = fopen("be.txt", "r");

  char utasitasok[101];

  fscanf(be, "%s", utasitasok);

  fclose(be);

  int eredmeny = csinal(utasitasok);

  FILE* ki = fopen("ki.txt", "w");

  fprintf(ki, "%d\n", eredmeny);

  fclose(ki);

  return 0;
}
