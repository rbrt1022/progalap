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
1. feladat (5 pont)

Szamold ki egy s1, s2, s3, ... szamtani sorozat elemeinek szorzatat. A
fuggveny megkapja a sorozat elso ket elemet (elso es masodik),
valamint egy egesz intervallum also (a) es felso (b) vegpontjat.
A fuggveny visszateresi erteke az sa*...*sb szorzat.
A szamtani sorozat n-edik eleme: sn=s1+(n-1)*d
*/

double sorozat(double elso, double masodik, int a, int b) {
    double d = masodik - elso;
    double eredmeny = elso, s[] = {0};

    for (int i = a; i < b+1; i++)
    {
        
        s[i] = elso + d * (i-1);

        eredmeny *= s[i];
        
        //printf("%lf\n", s[i]);
    }
    

    return eredmeny;
}

/*
2. feladat (5 pont)

A feladat egy fuggveny megirasa, amely parameterul
var egy fakbol allo tombot, annak hosszat, illetve
egy gyumolcs tipust. A fuggveny adja vissza azon
faknak az osszesitett termeset, amelyek tipusa
megegyezik a harmadik parameterkent kapott tipussal.
Amennyiben a tombben nem talalhato a parameterben kapott tipusu fa, akkor az eredmeny legyen -1.
A kis es nagybetuk egyformanak szamitanak.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen es a strukturan ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

typedef struct {
	char tipus; // a fa tipusa
	int magassag; // a fa magassaga
	int termes; // a fa termesenek mennyisege
} fa_t;

int ossztermes(fa_t fak[], int db, char tipus) {
    int ossz = 0;

    for (int i = 0; i < db; i++)
    {
        if (fak[i].tipus == tipus || fak[i].tipus == tipus+32)
        {
            ossz += fak[i].termes;
        }
        
    }
    
    return ossz;
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
	double e, m, eredmeny;
	int a, b;
	if(fscanf(stdin, "%lf %lf %d %d", &e, &m, &a, &b)!=4) {
		fprintf(stderr, "HIBA: Nem olvasható adat!\n");
		return;
	}
	eredmeny=sorozat(e, m, a, b);
	fprintf(stdout, "%.5lf\n", eredmeny);
}
void test_1()
{
  int i, err;
  double eredmeny;
  struct {double e; double m; int a; int b; double eredmeny;} testlist[2] = {{1.0, 3.0, 3, 5, 315.0}, {1.0, 1.5, 2, 4, 7.5}};
  fprintf(stderr, "=== 1. feladat tesztelése ===\n");
  for (i = 0; i < 2; ++i) {
    err = 0;
    fprintf(stderr, "%d. teszteset ... ", i + 1);
    eredmeny = sorozat(testlist[i].e, testlist[i].m, testlist[i].a, testlist[i].b);
    if (eredmeny != testlist[i].eredmeny) {
      err = 1;
      fprintf(stderr, "HIBA: sorozat(%lf, %lf, %d, %d)\n"
                      "\telvárt eredmény: %lf\n"
                      "\tkapott eredmény: %lf\n",
              testlist[i].e, testlist[i].m, testlist[i].a, testlist[i].b, testlist[i].eredmeny, eredmeny);
    }
    err ?: fprintf(stderr, "OK\n");
  }
}

void call_2(){
    int db;
    char tipus;
    fa_t *fak;
    if (fscanf(stdin, "%d %c\n", &db, &tipus) != 2) {
        fprintf(stderr, "HIBA: Nem olvasható adat (db, tipus)!\n");
        return;
    }
    fak = (fa_t*)malloc(db * sizeof(fa_t));
    for (int i = 0; i < db; ++i) {
        if(fscanf(stdin, "%c %d %d\n", &(fak[i].tipus), &(fak[i].magassag), &(fak[i].termes)) != 3) {
            fprintf(stderr, "HIBA: Nem olvasható adat (tipus, magassag, termes)!\n");
            free(fak);
            return;
        }
    }
    fprintf(stdout, "%d\n", ossztermes(fak, db, tipus));
    free(fak);
}
void test_2(){
    int i, err;
    int eredmeny;
    struct { fa_t fak[3]; int db; char tipus; int eredmeny; }
        testlist[2] = {
            {
                { {'a', 10, 5}, {'b', 4, 6}, {'a', 5, 2} }, 3, 'a', 7
            },
            {
                { {'a', 6, 5}, {'b', 7, 4}, {'B', 3, 8} }, 3, 'B', 12
            }
        };
    fprintf(stderr, "=== 2. feladat tesztelése ===\n");
    for (i = 0; i < 2; ++i) {
        err = 0;
        fprintf(stderr, "%d. teszteset ... ", i + 1);
        eredmeny = ossztermes(testlist[i].fak, testlist[i].db, testlist[i].tipus);
        if (eredmeny != testlist[i].eredmeny) {
            fprintf(stderr, "HIBA: ossztermes([{'%c',%d,%d},{'%c',%d,%d},{'%c',%d,%d}],%d,%c)\n"
                    "\telvárt eredmény: %d\n"
                    "\tkapott eredmény: %d\n",
                    testlist[i].fak[0].tipus, testlist[i].fak[0].magassag, testlist[i].fak[0].termes,
                    testlist[i].fak[1].tipus, testlist[i].fak[1].magassag, testlist[i].fak[1].termes,
                    testlist[i].fak[2].tipus, testlist[i].fak[2].magassag, testlist[i].fak[2].termes,
                    testlist[i].db, testlist[i].tipus,
                    testlist[i].eredmeny,
                    eredmeny
            );
            err = 1;
        }
        err ?: fprintf(stderr, "OK\n");
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
