int main() {
  int N;
  assume(N > 0);
  int a[N];
  int e;
  int i = 0;
  int j;

  while(i < N && a[i] != e) {
    i = i + 1;
  }

  for(int x = 0; x < i; x++) {
    assert(a[x] != e);
  }
  return 0;
}
