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

  i = 0;
  while(src[i] != 0) {
    assert(dst[i] == src[i]);
    i = i + 1;
  }
  return 0;
}

