#include <stdio.h>
#include <stdlib.h>

int main()
{
  //BEO
  FILE* beo = fopen("be.txt", "r");

  char bemenet[512];
  
  //Tömbbe való beo
  for (int i = 0; i < 512; i++)
  {
    fscanf(beo, "%c", &bemenet[i]);
    if (bemenet[i] == '\n')
    {
      break;
    }
    
  }
  
  //proba kiiratas
  int betuszamlalo = 0;
  for (int i = 0; bemenet[i] != '\n'; i++)
  {
    printf("%c", bemenet[i]);
    betuszamlalo++;
  }
  printf("\n");

  fclose(beo);

  //Karakterek tömbje
  char karakterek[6][6];
  char kar = 'a';

  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      printf("%d:%d\n", i,j);
      if (kar < 'z')
      {
        karakterek[i][j] = kar;
        kar++;
      }
      else if (kar == 'z')
      {
        karakterek[i][j] = kar;
        kar = '0';
      }
      else if (kar < '9')
      {
        karakterek[i][j] = kar;
        kar++;
      }
      
      
    }
    
  }

  //Karakterek kiir
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      printf("%c",karakterek[i][j]);
    }
    printf("\n");
  }

  //KIO
  FILE* kio = fopen("ki.txt", "w");

  fprintf(kio, "%d\n", betuszamlalo);

  //Kiderítés
  int helyes = 0;
  for (int a = 0; a<betuszamlalo; a++)
  {
    helyes = 0;
    for (int i = 0; i < 6; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        if (bemenet[a] == karakterek[i][j])
        {
          fprintf(kio, "%d%d\n", i+1, j+1);
          helyes = 1;
        }
        
      }
    }

    if (helyes == 0)
    {
      fprintf(kio, "HIBA:%d:%c\n", a, bemenet[a]);
      printf("HIBA:%d:%c\n", a, bemenet[a]);
    }
    
    
    
  }

  

  fclose(kio);
  return 0;
}