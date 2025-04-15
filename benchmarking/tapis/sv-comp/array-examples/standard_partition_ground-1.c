int main() {
  int N;
  assume(N > 0);
  int aa[N];
  int a = 0;
  int b = 0;
  int bb[N];

  while(a < N) {
    if(aa[a] >= 0) {
      bb[b] = aa[a];
      b = b + 1;
    }
    a = a + 1;
  }
  a = 0;
  int c = 0;
  int cc[N];
  while(a < N) {
    if(aa[a] >= 0) {
      cc[c] = aa[a];
      c = c + 1;
    }
    a = a + 1;
  }

  for(int x = 0; x < b; x++) {
    assert(bb[x] >= 0);
  }
  for(int y = 0; y < c; y++) {
    assert(cc[y] < 0);
  }
  return 0;
}


