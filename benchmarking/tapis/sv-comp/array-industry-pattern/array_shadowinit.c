int main() {
  int N;
  if(N > 0) {
    int i, k;
    int a[N];

    i = 0;
    k = 0;
    while(i < N) {
      a[k] = k;
      i = i + 1;
      k = k + 1;
    }

    for(int l = 0; l < N; l++) {
      assert(a[l] == l);
    }
  }
  return 0;
}
