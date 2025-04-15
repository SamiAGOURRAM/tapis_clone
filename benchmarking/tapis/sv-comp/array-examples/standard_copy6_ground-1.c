int main() {
  int N;
  assume(N > 0);
  int a1[N];
  int a2[N];

  int i;
  for(i = 0; i < N; i++) {
    a2[i] = a1[i];
  }
  int a3[N];
  for(i = 0; i < N; i++) {
    a3[i] = a2[i];
  }
  int a4[N];
  for(i = 0; i < N; i++) {
    a4[i] = a3[i];
  }
  int a5[N];
  for(i = 0; i < N; i++) {
    a5[i] = a4[i];
  }
  int a7[N];
  for(i = 0; i < N; i++) {
    a7[i] = a5[i];
  }
  int a6[N];
  for(i = 0; i < N; i++) {
    a7[i] = a6[i];
  }

  for(int x = 0; x < N; x++) {
    assert(a1[x] == a7[x]);
  }
  return 0;
}

