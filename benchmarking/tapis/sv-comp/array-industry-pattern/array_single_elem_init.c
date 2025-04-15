int main() {

  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];
  int c[SIZE];

  //init and update
  for(int i = 0; i < SIZE; i++) {
    bool q;
    a[i] = 0;
    if(!q) {
      a[i] = 1;
      b[i] = i % 2;
    }
    if(a[i] != 0) {
      if(b[i] == 0) {
        c[i] = 0;
      } else {
        c[i] = 1;
      }
    }
  }

  int iv;
  assume(0 <= iv && iv < SIZE);
  a[iv] = 1;

  for(int k = 0; k < SIZE; k++) {
    if(k == iv) {
      assert(c[k] == 0);
    }
  }
  return 0;
}

