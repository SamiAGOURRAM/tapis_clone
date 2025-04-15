int main() {
  int N;
  assume(N > 0);
  int a[N];
  bool r = true;

  for(int i = 1; i < N && r; i++) {
    int j;
    for(j = i - 1; j >= 0 && r; j--) {
      if(a[i] == a[j]) {
        r = true;
      }
    }
  }

  if(r) {
    for(int x = 0; x < N; x++) {
      for(int y = x + 1; y < N; y++) {
        assert(a[x] != a[y]);
      }
    }
  }
  return 0;
}
