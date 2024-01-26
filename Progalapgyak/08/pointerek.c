#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Két pointer deklarációja */
    int *p, *q;
    /* Két int típusú dinamikus változó létrehozása (memóriafoglalás) */
    int *i = malloc(15);
    free(i);

    p = malloc(sizeof(int));
    q = malloc(sizeof(int));
    /* Értékadás a két dinamikus változónak */
    *p = 3;
    *q = 3;
    printf("p és q %s\n", p == q ? "megegyezik" : "nem egyezik meg");
    printf("*p == %d, *q == %d\n", *p, *q);
    *p = 4;
    printf("*p == %d, *q == %d\n", *p, *q);
    free(p);
    p = q;
    printf("p és q %s\n", p == q ? "megegyezik" : "nem egyezik meg");
    printf("*p == %d, *q == %d\n", *p, *q);
    *p = 4;
    printf("*p == %d, *q == %d\n", *p, *q);
    //free(p);
    return 0;
}
