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

A lejto() fuggveny feladata kiszamolni azt, hogy mekkora ereszkedest kell vegrehajtani
a legnagyobb szintkulonbsegu szakasz lekuzdesehez egy szakaszokbol felepulo hegyvideki tura soran.
A parameterben kapott terkep tomb a turautvonal szakaszait zaro allomasok tengerszint 
feletti magassagertekeit tartalmazza. A tombot a -1 ertek zarja. A fuggveny kiszamolna, 
hogy mekkora a legnagyobb kulonbseg a kovetkezo es az aktualis allomas kozott, ott 
ahol a kovetkezo allomas eleresehez lefele kell haladni.
Vedd szemugyre a probainputot es a hozza tartozo kimenetet.

A fuggveny megvalositasa hibakat tartalmaz.
Javitsd ki ezeket a hibakat.
*/
int lejto(int terkep[]) {
    /*int szint = 0;
    int maxszint = szint;
    int i;
    for (i = 0; terkep[i] != -1; ++i) {
        if (terkep[i] > terkep[i+1]) {
            szint = terkep[i] + terkep[i+1];
            if (szint > maxszint) {
                maxszint = szint;
            }
        } else {
            szint = 0;
        }
    }
    return szint;*/

    int szint = 0;
    int i;
    int maxszint = 0;
    for (i = 0; terkep[i] != -1; ++i) {
        szint = terkep[i] - terkep[i+1];
        if (szint > maxszint && terkep[i+1] != -1)
        {
            //printf("Szint: %d", szint);
            maxszint = szint;
        }
        
    }
    return maxszint;
}

/*
2. feladat (5 pont)

A feladat egy fuggveny megirasa, amely parameterul var egy egesz szamokbol
allo tombot, illetve ket egesz szamra mutato pointert.
A tombben egesz szamok vannak, a tomb veget a 0 ertek jelzi.

A fuggveny feladata, hogy meghatarozza a tombben levo elemek kozul a
legnagyobb pozitiv, illetve legnagyobb negativ erteket.
A maxPozitiv pointer altal mutatott ertek legyen a legnagyobb pozitiv
szam, mig a maxNegativ altal mutatott ertek pedig a legnagyobb negativ
szam, ami a tombben elofordul. Amennyiben a tombben egy
pozitiv / negativ ertek sem fordul elo, akkor a pointer altal
mutatott ertek legyen a tomb veget jelzo ertek.

Kodold le C nyelven a fuggvenyt! A fuggveny fejlecen ne valtoztass!
A fuggveny inputjai a parameterek, outputja a visszateresi ertek.
A fuggveny nem vegez IO muveleteket!
*/

void statisztika(int szamok[], int* maxPozitiv, int* maxNegativ) {
    //Maxpozitív megh
    *maxPozitiv = 0;
    for (int i = 0; szamok[i] != 0; i++)
    {
        if (i == 0 && szamok[i] > 0)
        {
            *maxPozitiv = szamok[i];
        }
        else if (szamok[i] > szamok[i+1] && szamok[i] > 0)
        {
            *maxPozitiv = szamok[i];
        }
        else if (szamok[i] > szamok[i+1] && szamok[i] <= 0)
        {
            *maxPozitiv = 0;
        }
        
        
        
    }

    //Maxnegatív
    *maxNegativ = 0;
    for (int i = 0; szamok[i] != 0; i++)
    {
        if (i == 0)
        {
            *maxNegativ = szamok[i];
        }
        else if (szamok[i] > szamok[i-1] && szamok[i] < 0) 
        {
            *maxNegativ = szamok[i];
        }
        else if (szamok[i] > szamok[i+1] && szamok[i] >= 0)
        {
            *maxNegativ = 0;
        }
        
        
        
    }
    
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
    int i, n, terkep[128];

    if(fscanf(stdin, "%d\n", &n)!=1) {
        fprintf(stderr, "HIBA: Nem olvasható adat!\n");
        return;
    }

    for (i=0; i<n; ++i) {
        if (fscanf(stdin, "%d", terkep + i)!=1) {
            fprintf(stderr, "HIBA: Nem olvasható adat!\n");
            return;
        }
    }

    fprintf(stdout, "%d\n", lejto(terkep));
}
void test_1()
{
  int i, j, eredmeny;
  struct {int terkep[128]; int eredmeny;} testlist[1] = {
    {{150,134,132,112,101,90,90,163,152,147,140,140,130,-1}, 20},
  };
  fprintf(stderr, "=== 1. feladat tesztelése ===\n"); 
  for (i = 0; i < 1; ++i) {
    fprintf(stderr, "%d. teszteset ... ", i + 1);
    eredmeny = lejto(testlist[i].terkep);
    if (eredmeny != testlist[i].eredmeny) {
      fprintf(stderr, "HIBA: lejto({");
      for(j = 0; testlist[i].terkep[j] != -1; fprintf(stderr, "%d,", testlist[i].terkep[j++]));
      fprintf(stderr, "-1})\n"
                      "\telvárt eredmény: %d\n"
                      "\tkapott eredmény: %d\n",
                      testlist[i].eredmeny, eredmeny);
    } else
      fprintf(stderr, "OK\n");
  }
}

void call_2()
{
	int meret;

	if(fscanf(stdin, "%d", &meret) != 1) {
		fprintf(stderr, "HIBA: Nem olvasható adat (meret)!\n");
		return;
	}

	int tomb[meret];
	for (int i = 0; i < meret; i++) {
		if(fscanf(stdin, "%d", &tomb[i]) != 1) {
			fprintf(stderr, "HIBA: Nem olvasható adat (tomb[%d])!\n", i);
			return;
		}
	}

	int *ptrPozitiv = (int*)malloc(sizeof(int));
	if (ptrPozitiv == NULL) {
		fprintf(stderr, "HIBA: Nem foglalható memória (ptrPozitiv)\n");
		return;
	}

	int *ptrNegativ = (int*)malloc(sizeof(int));
	if (ptrNegativ == NULL) {
		fprintf(stderr, "HIBA: Nem foglalható memória (ptrNegativ)\n");
		return;
	}

	*ptrPozitiv = 1234;
	*ptrNegativ = -1234;

	statisztika(tomb, ptrPozitiv, ptrNegativ);

	if (ptrPozitiv != NULL) {
		fprintf(stdout, "%d\n", *ptrPozitiv);
		free(ptrPozitiv);
	} else {
		fprintf(stdout, "NULL\n");
	}

	if (ptrNegativ != NULL) {
		fprintf(stdout, "%d\n", *ptrNegativ);
		free(ptrNegativ);
	} else {
		fprintf(stdout, "NULL\n");
	}
}
void test_2()
{
	struct {int tomb[5]; int maxPozitiv; int maxNegativ;} testlist[2] = {
		{ { 1, 5, -4, -3, 0}, 5, -3 },
		{ { -6, -2, -3, -5, 0}, 0, -2 },
	};
	fprintf(stderr, "=== 2. feladat tesztelése ===\n");
	for (int i = 0; i < 2; ++i) {
		fprintf(stderr, "%d. teszteset ... ", i + 1);
		int *ptrPozitiv = (int*)malloc(sizeof(int));
		int *ptrNegativ = (int*)malloc(sizeof(int));
		statisztika(testlist[i].tomb, ptrPozitiv, ptrNegativ);
		if (ptrPozitiv == NULL) {
			fprintf(stderr, "HIBA: NULL pointer (maxPozitiv)\n");
			if (ptrNegativ) free(ptrNegativ);
			continue;
		}
		if (ptrNegativ == NULL) {
			fprintf(stderr, "HIBA: NULL pointer (maxNegativ)\n");
			if (ptrPozitiv) free(ptrPozitiv);
			continue;
		}
		if (*ptrPozitiv != testlist[i].maxPozitiv || *ptrNegativ != testlist[i].maxNegativ) {
			fprintf(stderr, "HIBA statisztika({");
			int j = 0; for (; testlist[i].tomb[j] != 0; fprintf(stderr, "%d,", testlist[i].tomb[j++]));
			fprintf(stderr, "%d})\n"
				"\telvárt eredmény: %d %d\n"
				"\tkapott eredmény: %d %d\n",
				testlist[i].tomb[j],
				testlist[i].maxPozitiv, testlist[i].maxNegativ,
				*ptrPozitiv, *ptrNegativ);
		} else
			fprintf(stderr, "OK\n");
		if (ptrPozitiv) free(ptrPozitiv);
		if (ptrNegativ) free(ptrNegativ);
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
