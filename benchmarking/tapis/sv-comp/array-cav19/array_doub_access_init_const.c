int main() {
  int N;
  assume(N >= 0);
  int a[2 * N + 2];

  for(int i = 0; i <= N; i++) {
    a[2 * i] = 0;
    a[2 * i + 1] = 0;
  }

  for(int k = 0; k <= 2 * N; k++) {
    assert(a[k] >= 0);
  }
  return 0;
}
