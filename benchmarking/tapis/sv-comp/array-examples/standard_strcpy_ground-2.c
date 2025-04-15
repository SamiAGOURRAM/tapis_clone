int main() {
  int N;
  assume(N > 0);
  int src[N];
  int dst[N];

  int i = 0;
  while(src[i] != 0) {
    dst[i] = src[i];
    i = i + 1;
  }

  for(int x = 0; x < i; x++) {
    assert(dst[x] == src[x]);
  }
  return 0;
}

