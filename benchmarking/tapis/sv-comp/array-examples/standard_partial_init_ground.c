int main() {
  int N;
  assume(N > 0);
  int A[N];
  int B[N];
  int C[N];
  int i;
  int j = 0;

  for(i = 0; i < N; i++) {
    if(A[i] == B[i]) {
      C[j] = i;
      j = j + 1;
    }
  }


  for(int x = 0; x < j; x++) {
    assert(C[x] <= x + i - j);
  }
  for(int y = 0; y < j; y++) {
    assert(C[y] >= y);
  }
  return 0;
}
