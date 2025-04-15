bool _strcmp(int src[], int dst[], int N) {
  int i = 0;
  while(i < N) {
    if(dst[i] != src[i]) return true;
    i = i + 1;
  }
  return false;
}


int main() {
  int N;
  assume(N > 0);
  int a[N];
  int b[N];

  bool c = _strcmp(a, b, N);

  if(!c) {
    for(int x = 0; x < N; x++) {
      assert(a[x] == b[x]);
    }
  }
  return 0;
}
