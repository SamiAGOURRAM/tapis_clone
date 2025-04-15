int main() {
  int N;
  assume(N > 0);
  int a[N];
  int marker;
  int pos;

  if(pos >= 0 && pos < N) {
    a[pos] = marker;

    int i = 0;
    while(a[i] != marker) {
      i = i + 1;
    }

    assert(i <= pos);
  }
  return 0;
}
