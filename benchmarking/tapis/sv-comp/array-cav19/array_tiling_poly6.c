int main() {
  int S;
  assume(S > 0);
  int a[S];

  int i;
  for(i = 0; i < S; i++) {
    a[i] = ((i - 1) * (i + 1));
  }

  for(i = 0; i < S; i++) {
    a[i] = a[i] - (i * i);
  }

  for(int k = 0; k < S; k++) {
    assert(a[k] == -1);
  }
  return 0;
}

