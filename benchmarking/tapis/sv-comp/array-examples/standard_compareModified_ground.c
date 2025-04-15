int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];
  int c[SIZE];

  int i = 0;
  bool rv = true;
  while(i < SIZE) {
    if(a[i] != b[i]) {
      rv = false;
    }
    c[i] = a[i];
    i = i + 1;
  }

  if(rv) {
    for(int k = 0; k < SIZE; k++) {
      assert(a[k] == b[k]);
    }
  }

  for(int x = 0; x < SIZE; x++) {
    assert(a[x] == c[x]);
  }
  return 0;
}
