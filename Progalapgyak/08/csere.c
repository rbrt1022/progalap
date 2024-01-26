#include <stdio.h>

void csere(int *a, int *b) {
    printf("a=%p b=%p *a=%d *b=%d\n", a, b, *a, *b);

    int tmp;

    tmp = *a;
    *a   = *b;
    *b   = tmp;

    printf("a=%p b=%p *a=%d *b=%d\n", a, b, *a, *b);
}

int main() {
    int x = 3, y = 5;

    printf("A függvény előtt: x = %d, y = %d\n", x, y);

    csere(&x, &y);

    printf("A függvény után: x = %d, y = %d\n", x, y);

    return 0;
}
