int main() {
  int N;
  assume(N > 0);
  int a1[N];
  int a2[N];

  int z;
  assume(0 <= z && z < N);

  int i;
  for(i = 0; i < N; i++) {
    if(i != z)
      a2[i] = a1[i];
  }

  z = z + 1;
  for(i = 0; i < N; i++) {
    if(i != z)
      assert(a1[i] == a2[i]);
  }
  return 0;
}

