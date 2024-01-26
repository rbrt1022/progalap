int siknegyed(double x, double y) {
  if (x > 0 && y > 0) {
    return 1;
  } else if (x < 0 && y > 0) {
    return 2;
  } else if (x < 0 && y < 0) {
    return 3;
  } else {
    return 4;
  }
}

int lnko(int a, int b) {
  if (a == 0 && b == 0) {
    return -1;
  }

  int seged = 1;

  for (int o = 1; o < a + b + 1; ++o) {
    if (a % o == 0 && b % o == 0) {
      seged = o;
    }
  }

  return seged;
}