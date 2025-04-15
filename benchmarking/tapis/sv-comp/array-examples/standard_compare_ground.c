int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];

  int i = 0;
  bool rv = true;
  while(i < SIZE) {
    if(a[i] != b[i]) {
      rv = false;
    }
    i = i + 1;
  }

  if(rv) {
    for(int x = 0; x < SIZE; x++) {
      assert(a[x] == b[x]);
    }
  }
  return 0;
}
