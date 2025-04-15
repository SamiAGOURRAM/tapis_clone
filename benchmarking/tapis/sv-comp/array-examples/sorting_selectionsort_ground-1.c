int main() {
  int N;
  assume(N > 0);
  int a[N];

  int i = 0;
  while(i < N) {
    int k = i + 1;
    int s = i;
    while(k < N) {
      if(a[k] < a[s]) {
        s = k;
      }
      k = k + 1;
    }
    if(s != i) {
      int tmp = a[s];
      a[s] = a[i];
      a[i] = tmp;
    }

    for(int x = 0; x < i; x++) {
      for(int y = x + 1; y < i; y++) {
        assert(a[x] <= a[y]);
      }
    }
    for(int y = 0; y < N; y++) {
      assert(a[y] >= a[i]);
    }

    i = i + 1;
  }

  for(int x = 0; x < N; x++) {
    for(int y = x + 1; y < N; y++) {
      assert(a[x] <= a[y]);
    }
  }
  return 0;
}
