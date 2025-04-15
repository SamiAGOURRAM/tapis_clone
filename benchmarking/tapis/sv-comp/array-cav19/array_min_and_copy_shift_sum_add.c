int main() {
  int N;
  assume(N > 0);
  int k = 0;
  int a[N + 1];
  int b[N];

  int j;
  int i;
  for(i = 0; i < N; i++) {
    if(j > a[i]) {
      j = a[i];
    }
  }

  for(i = 0; i < N; i++) {
    b[i] = a[i] - j;
  }

  for(i = 0; i < N; i++) {
    k = k + b[i] + i;
  }

  assert(k >= 0);
  return 0;
}
