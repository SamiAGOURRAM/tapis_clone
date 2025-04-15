int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];
  int c[SIZE];
  int i = 0;

  i = 0;
  while(i < SIZE) {
    c[i] = a[i] - b[i];
    i = i + 1;
  }

  for(int x = 0; x < SIZE; x++) {
    assert(c[x] == a[x] - b[x]);
  }
  return 0;
}

