#include <stdio.h>
#include <stdlib.h>

int* foglal_sorfolytonos(int sorok, int oszlopok) {
  int* tomb = malloc(sizeof(int) * sorok * oszlopok);

  return tomb;
}

void feltolt_sorfolytonos(int* tomb, int sorok, int oszlopok) {
  for (int i = 0; i < sorok * oszlopok; ++i) {
    tomb[i] = (i + 1);
  }
}

void kiir_sorfolytonos(int* tomb, int sorok, int oszlopok) {
  for (int sor = 0; sor < sorok; ++sor) {
    for (int oszlop = 0; oszlop < oszlopok; ++oszlop) {
      int k = sor * oszlopok + oszlop;

      printf("%3d", tomb[k]);
    }

    printf("\n");
  }
}

int** foglal_valos2d(int sorok, int oszlopok) {
  int** t = malloc(sizeof(int*) * sorok);

  for (int sor = 0; sor < sorok; ++sor) {
    t[sor] = malloc(sizeof(int) * oszlopok);
  }

  return t;
}

void feltolt_valos2d(int** tomb, int sorok, int oszlopok) {
  int i = 1;

  for (int sor = 0; sor < sorok; ++sor) {
    for (int oszlop = 0; oszlop < oszlopok; ++oszlop) {
      tomb[sor][oszlop] = i;

      ++i;
    }
  }
}

void kiir_valos2d(int** tomb, int sorok, int oszlopok) {
  for (int sor = 0; sor < sorok; ++sor) {
    for (int oszlop = 0; oszlop < oszlopok; ++oszlop) {
      printf("%3d", tomb[sor][oszlop]);
    }

    printf("\n");
  }
}

void free_valos2d(int** tomb, int sorok) {
  for (int sor = 0; sor < sorok; ++sor) {
    free(tomb[sor]);
  }

  free(tomb);
}

int main() {
  int* t = foglal_sorfolytonos(2, 3);

  feltolt_sorfolytonos(t, 2, 3);
  kiir_sorfolytonos(t, 2, 3);
  
  free(t);

  int** t2 = foglal_valos2d(2, 3);

  feltolt_valos2d(t2, 2, 3);
  kiir_valos2d(t2, 2, 3);

  free_valos2d(t2, 2);

  return 0;
}
