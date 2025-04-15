int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  for(int i = 0; i < SIZE; i++) {
    a[i] = 10;
  }

  int z;
  assume(0 <= z && z < SIZE);

  for(int j = 0; j < SIZE; j++) {
    assert(a[j] == 10);
    if(j + 1 != z) {
      a[j + 1] = 20;
    }
  }

  return 0;
}

