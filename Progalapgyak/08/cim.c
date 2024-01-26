#include <stdio.h>

int main() {
    int a = 20;
    int *pa;
    //int* pa;
    //int  *    pa;

    pa = &a;

    printf(" a=%d   pa=%p\n", a, pa);
    printf("&a=%p  &pa=%p\n", &a, &pa);

    printf("*pa=%d\n", *pa);

    return 0;
}
