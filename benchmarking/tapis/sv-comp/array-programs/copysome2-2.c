int main() {
  int N;
  assume(N > 0);
  int a1[N];
  int a2[N];
  int a3[N];

  int i;
  int z;
  assume(0 <= z && z < N);

  for(i = 0; i < N; i++) {
    if(i != z)
      a2[i] = a1[i];
  }
  for(i = 0; i < N; i++) {
    if(i != z)
      a3[i] = a2[i];
    else
      a3[i] = a1[i];
  }

  for(int x = 0; x < N; x++) {
    assert(a2[x] == a3[x]);
  }
  return 0;
}

