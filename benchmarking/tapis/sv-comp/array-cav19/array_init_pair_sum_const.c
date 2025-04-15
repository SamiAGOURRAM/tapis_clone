int main() {
  int N;
  assume(N > 0);
  int a[N];
  int b[N];

  int i;
  for(i = 0; i < N; i++) {
    a[i] = 1;
    b[i] = 2;
  }

  int c[N];
  for(i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
  }

  for(int k = 1; k < N; k++) {
    assert(c[k] >= 3);
  }
  return 0;
}


