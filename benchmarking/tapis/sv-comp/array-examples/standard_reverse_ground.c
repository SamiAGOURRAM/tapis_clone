int main() {
  int N;
  assume(N > 0);
  int a[N];
  int b[N];
  int i;
  for(i = 0; i < N; i++) {
    b[i] = a[N - i - 1];
  }

  for(int x = 0; x < N; x++) {
    assert(a[x] == b[N - x - 1]);
  }
  return 0;
}
