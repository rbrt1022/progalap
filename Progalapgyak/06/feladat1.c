int tombosszefuzes(int tomb[], int eredmeny[], int fuznivalo[], int meret, int fmeret) {
  int i;

  for (i = 0; i < meret; ++i) {
    eredmeny[i] = tomb[i];
  }

  for (int j = 0; j < fmeret; ++j, ++i) {
    //eredmeny[meret + i] = fuznivalo[i];
    eredmeny[i] = fuznivalo[j];
  }

  //return meret + fmeret;
  return i;
}