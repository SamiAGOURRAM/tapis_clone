int main() {
  int N;
  assume(N > 0);
  int A[N];
  int i;
  for(i = 0; i < N / 2; i++) {
    A[i] = A[N - i - 1];
  }

  for(int x = 0; x < N / 2; x++) {
    assert(A[x] == A[N - x - 1]);
  }
  return 0;
}
