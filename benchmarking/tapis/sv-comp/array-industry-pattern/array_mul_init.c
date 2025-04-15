int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];

  int i;
  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = i;
  }

  for(i = 0; i < SIZE; i++) {
    bool bo;
    if(bo) {
      int k;
      a[i] = k;
      b[i] = k * k;
    }
  }

  for(int l = 0; l < SIZE; l++) {
    assert(a[l] == b[l] || b[l] == a[l] * a[l]);
  }
}

