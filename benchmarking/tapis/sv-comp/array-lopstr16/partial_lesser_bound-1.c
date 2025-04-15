int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  for(int i = 0; i < SIZE; i++) {
    a[i] = 0;
  }

  for(int j = 0; j < SIZE / 2; j++) {
    a[j] = 10;
  }


  for(int k = 0; k < SIZE / 2; k++) {
    assert(a[k] == 10);
  }

  return 0;
}	


