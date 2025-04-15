int main() {
  int N;
  assume(N > 0);
  int a[N];

  bool swapped = true;
  while(swapped) {
    swapped = false;
    int i = 1;
    while(i < N) {
      if(a[i - 1] < a[i]) {
        int t = a[i];
        a[i] = a[i - 1];
        a[i - 1] = t;
        swapped = true;
      }
      i = i + 1;
    }
  }

  for(int x = 0; x < N; x++) {
    for(int y = x + 1; y < N; y++) {
      assert(a[x] <= a[y]);
    }
  }
  return 0;
}
