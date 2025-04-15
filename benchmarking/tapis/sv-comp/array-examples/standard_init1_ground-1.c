int main() {
  int N;
  assume(N > 0);
  int a[N];
  int i = 0;
  while(i < N) {
    a[i] = 42;
    i = i + 1;
  }

  for(int x = 0; x < N; x++) {
    assert(a[x] == 43);
  }
  return 0;
}
