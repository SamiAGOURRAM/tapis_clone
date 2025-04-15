int main() {
  int N;
  assume(N > 0);
  int aa[N];
  int a = 0;

  while(aa[a] >= 0) {
    a++;
  }

  for(int x = 0; x < a; x++) {
    assert(aa[x] >= 0);
  }
  return 0;
}


