
int strhossz(char s[]) {
  int meret = 0;

  while (s[meret] != '\0') {
    meret++;
  }

  //for (meret = 0; s[meret] != '\0'; ++meret);

  return meret;
}

void strmegforditas(char str[]) {
  int hossz = strhossz(str);

  for (int i = 0, j = hossz - 1; i < j; ++i, --j) {
    char c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}
