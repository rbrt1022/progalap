#include "paint.h"

void felhocske(float meret) {
  if (meret < 50) {
    return;
  }

  draw_cloud(meret);

  felhocske(meret - 20);
}

void oldal(float hossz, int n) {
  if (n == 0) {
    forward(hossz);
  } else {
    hossz /= 3;

    //forward(hossz);
    oldal(hossz, n - 1);
    left(60);
    //forward(hossz);
    oldal(hossz, n - 1);
    right(120);
    //forward(hossz);
    oldal(hossz, n - 1);
    left(60);
    //forward(hossz);
    oldal(hossz, n - 1);
  }
}

void alakzat(float hossz) {
  for (int i = 1; i <= 3; ++i) {
    oldal(hossz, 4);
    right(120);
  }
}

int main() {
    create_window(500, 500);

    set_speed(10);

    //felhocske(250);
    alakzat(210);


    close_window();
    return 0;
}
