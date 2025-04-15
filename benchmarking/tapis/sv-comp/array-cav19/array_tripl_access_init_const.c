int main() {
  int N;
  assume(N >= 0);
  int a[3 * N + 1];

  int i;
  for(i = 0; i <= N; i++) {
    a[3 * i] = 0;
    a[3 * i + 1] = 0;
    a[3 * i + 2] = 0;
  }

  for(int k = 0; k <= 3 * N; k++) {
    assert(a[k] >= 0);
  }
  return 0;
}

