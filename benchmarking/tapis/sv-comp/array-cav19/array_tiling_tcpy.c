int main() {
  int S;
  assume(S > 1);
  int a[2 * S];
  int acopy[2 * S];

  for(int i = 0; i < S; i++) {
    acopy[2 * S - (i + 1)] = a[2 * S - (i + 1)];
    acopy[i] = a[i];
  }

  for(int k = 0; k < 2 * S; k++) {
    assert(acopy[k] == a[k]);
  }
  return 0;
}

