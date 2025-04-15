int main() {
  int N;
  assume(N > 0);
  int a[N];
  int max = 0;

  int i = 0;
  while(i < N) {
    if(a[i] > max) {
      max = a[i];
    }
    i = i + 1;
  }

  for(int x = 0; x < N; x++) {
    assert(a[x] <= max);
  }
  return 0;
}
