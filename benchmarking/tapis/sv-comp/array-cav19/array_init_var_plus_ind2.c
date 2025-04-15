int main() {
  int N;
  assume(N > 0);
  int j = 0;
  int k = 0;
  int a[N];

  int i;
  for(i = 0; i < N; i++) {
    bool x;
    if(x) {
      break;
    }
    a[i] = j;
    j = j + i;
    k = k - i;
  }

  for(int l = 1; l < i; l++) {
    assert(a[l] >= k);
  }
  return 0;
}

