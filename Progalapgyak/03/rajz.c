#include "paint.h"

void negyzet() {
  for (int i = 1; i <= 4; i++) {
    forward(75);
    right(90);
  }
}

void sokszog(float oldal_hossz, int oldal_szam) {
  for (int i = 1; i <= oldal_szam; i++) {
    forward(oldal_hossz);
    right(360.0 / oldal_szam);
  }
}

int main() {
    create_window(500, 500);

    set_speed(5);
    //negyzet();
    sokszog(75, 4);
    sokszog(50, 8);
    sokszog(10, 100);


    close_window();
    return 0;
}
