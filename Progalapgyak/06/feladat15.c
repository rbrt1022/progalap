void strtorles(char str[], char eredmeny[], int darab) {
  int i, j;

  // A:
  int meret = 0;

  while (str[meret] != '\0') {
    ++meret;
  }

  for (i = 0, j = darab; j < meret && str[j] != '\0'; ++i, ++j) {
    eredmeny[i] = str[j];
  }

  // B:
  for (i = 0, j = 0; str[i] != '\0'; ++i) {
    if (i >= darab) {
      eredmeny[j] = str[i];
      ++j;
    }
  }

  // A:
  eredmeny[i] = '\0';
  // B:
  eredmeny[j] = '\0';
}
