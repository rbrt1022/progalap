/*
 * Szegedi Tudományegyetem
 * Informatikai Tanszékcsoport
 * Szoftverfejlesztés Tanszék
 *
 * Programozás Alapjai
 */

#include <stdio.h>

int main() {
    int elso = 0, masodik = 0, harmadik = 0;
    printf("L12: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);
    //int elso = 1;
    elso = 1;

    printf("L14: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);

    {
        int masodik = 2;
        printf("L17: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);
    }

    printf("L19: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);

    {
        int harmadik = 3;
        printf("L22: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);
    }

    printf("L24: e= %d; m= %d; h= %d;\n", elso, masodik, harmadik);

    return 0;
}
