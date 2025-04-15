int main() {
  int N;
  assume(N > 0);
  int a1[N];
  int a2[N];

  for(int i = 0; i < N; i++) {
    a2[i] = a1[i];
  }

  for(int x = 0; x < N; x++) {
    assert(a1[x] == a2[x]);
  }
  return 0;
}

