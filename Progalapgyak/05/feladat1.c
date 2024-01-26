int karoszt(char c) {
  if ('A' <= c && c <= 'Z') {
    return 2;
  } else if ('0' <= c && c <= '9') {
    return 1;
  } else {
    return -1;
  }
}

int osztoosszeg(int n) {
  int osszeg = 0;

  //int oszto = 1;
  //int x = oszto++;

  // prefix: x == 2, oszto == 2
  // postfix: x == 1, oszto == 2

  for (int oszto = 1; oszto <= n / 2; oszto++) {
    if (n % oszto == 0) {
      osszeg += oszto;
    }
  }

  return osszeg;
}