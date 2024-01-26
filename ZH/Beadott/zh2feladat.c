/***********************************************************************
* A PROGRAMBAN NEM SZEREPELHETNEK AZ ALÁBBI SOROK:
* #include <string.h>
* #include <math.h>
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
************************************************************************
**  ETTŐL A PONTTÓL DOLGOZHATSZ A FELADATOKON
************************************************************************
***********************************************************************/

/*
1. feladat (2 pont)

A feladat a karakterek osztalyozasara szolgalo karoszt fuggveny megirasa. A fuggveny
parameterben egy karaktert kap. Amennyiben ez a karakter nagybetu terjen vissza 2-vel,
ha szamjegy 1-gyel, minden mas esetben pedig -1 legyen a visszateresi ertek.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputja a parameter, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int karoszt(char c) {
    //Nagybetűk:
    if (c >= 65 && c <= 96)
    {
        //printf("Nagybetű\n");
        return 2;
    }
    //Kisbetűk:
    else if ((c >= 97 && c <= 122))
    {
        //printf("Kisbetű\n");
        return 1;
    }
    else
    {
        //printf("Egyik se");
        return -1;
    }
    
    
}

/*
2. feladat (3 pont)
 
A feladat meghatarozni egy szam onmagan kivuli osztoinak osszeget. A fuggveny
egyetlen parametere a kerdeses szam, amelyrol meg kell mondani, hogy mi a
pozitiv egesz osztoinak osszege. A visszateresi ertek ez a szam.

A szamitas elvegezheto egy olyan ciklussal, ami 1-tol n/2-ig megy, es
minden lepesben megvizsgalja, hogy a ciklusvaltozo aktualis erteke osztoja-e
a parameternek, azaz elosztva vele a parametert 0 maradekot kapunk-e.
Ha igen, akkor ezzel noveljuk az osztok osszeget tarolo valtozo erteket,
amivel majd a fuggveny a ciklus befejezese utan visszater.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

int osztoosszeg(int n) {
    int lepteto1 = 0, szumosztok = 0;
    //int cucc = n/2
    while (lepteto1 <= n/2)
    {
        //printf("Lefutok %d. alkalommal:", lepteto1);
        if (n % lepteto1 == 0)
        {
            szumosztok += lepteto1;
        }
        
        lepteto1++;
    }

    return szumosztok;
    
}
/***********************************************************************
************************************************************************
**
**  EZEN A PONTON TÚL NE VÁLTOZTASS SEMMIT SEM A FÁJLON!
**
************************************************************************
***********************************************************************/

void call_1()
{
    char kar;
    int eredmeny;
    if(fscanf(stdin, "%c", &kar)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }
    eredmeny=karoszt(kar);
    fprintf(stdout, "%d\n", eredmeny);
}
void test_1()
{
    int eredmeny, i;
    struct {char c; int eredmeny;} testlist[2] = {{'G', 2}, {'x', -1}};
    for (i = 0; i < 2; ++i) {
        eredmeny = karoszt(testlist[i].c);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: karoszt('%c')\n"
                            "\telvárt eredmény: %d\n"
                            "\tkapott eredmény: %d\n",
                testlist[i].c, testlist[i].eredmeny, eredmeny);
        }
    }
}

void call_2()
{
	int n, eredmeny;
	if(fscanf(stdin, "%d", &n)!=1) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny=osztoosszeg(n);
	fprintf(stdout, "%d\n", eredmeny);
}
void test_2()
{
	int eredmeny, i;
	struct {int szam; int eredmeny;} testlist[2] = {{6, 6}, {24, 36}};
	for (i = 0; i < 2; ++i) {
		eredmeny = osztoosszeg(testlist[i].szam);
		if (eredmeny != testlist[i].eredmeny) {
			fprintf(stderr, "HIBA: osztoosszeg(%d)\n"
							"\telvárt eredmény: %d\n"
							"\tkapott eredmény: %d\n",
				testlist[i].szam, testlist[i].eredmeny, eredmeny);
		}
	}
}

typedef void (*call_function)();

call_function call_table[] = {
	call_1,
	call_2,
	NULL
};


call_function test_table[] = {
	test_1,
	test_2,
	NULL
};

static int __arg_check_helper(const char * exp, const char * arg) {
    while (*exp && *arg && *exp == *arg) {
        ++exp;
        ++arg;
    }
    return *exp == *arg;
}

int main(int argc, char *argv[])
{
    int feladat, calltabsize;
    if ((argc > 1) && !(__arg_check_helper("-t", argv[1]) && __arg_check_helper("--test", argv[1]))) {
        if (argc > 2) {
            feladat = atoi(argv[2]);
            for (calltabsize=0; test_table[calltabsize]; calltabsize++);
            if (feladat <= 0 || calltabsize < feladat) {
                fprintf(stderr, "HIBA: rossz feladat sorszám: %d!\n", feladat);
                return 1;
            }
            (*test_table[feladat-1])();
        } else {
            for (feladat=0; test_table[feladat]; ++feladat) {
                (*test_table[feladat])();
            }
        }
        return 0;
    }
    if (!freopen("be.txt", "r", stdin)) {
        fprintf(stderr, "HIBA: Hiányzik a `be.txt'!\n");
        return 1;
    }
    if (!freopen("ki.txt", "w", stdout)) {
        fprintf(stderr, "HIBA: A `ki.txt' nem írható!\n");
        return 1;
    }
    for (calltabsize=0; call_table[calltabsize]; calltabsize++);
    if (fscanf(stdin, "%d%*[^\n]", &feladat)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható a feladat sorszám!\n");
        return 1;
    }
    fgetc(stdin);
    if (0<feladat && feladat<=calltabsize) {
        (*call_table[feladat-1])();
    } else {
        fprintf(stderr, "HIBA: Rossz feladat sorszám: %d!\n", feladat);
        return 1;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
