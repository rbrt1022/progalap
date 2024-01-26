int tombertektorles(int tomb[], int torlendo, int meret) {
  int j = 0;

  for (int i = 0; i < meret; ++i) {
    if (tomb[i] != torlendo) {
      tomb[j] = tomb[i];
      j++;
    }
  }

  return j;
}