#include <stdio.h>

int main()
{
  //dekl
  char karakter[100];

  //Fájlbeo
  FILE* be;
  be = fopen("be.txt","r");
  for (int i = 0; i < 100; i++)
  {
    fscanf(be, "%c", &karakter[i]);
  }
  
  

  //Fájlkiír
  FILE* ki;
  ki = fopen("ki.txt","w");
  fprintf(ki, "%s", karakter);

  return 0;
}