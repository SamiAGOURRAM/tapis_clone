int main() {
  int N;
  assume(N > 0);
  int j = 0;
  int a[N];

  int i;
  for(i = 0; i < N; i++) {
    bool x;
    if(x) {
      break;
    }
    a[i] = j;
    j = j + i;
  }

  for(int k = 1; k < i; k++) {
    assert(a[k] >= 0);
  }
  return 0;
}

