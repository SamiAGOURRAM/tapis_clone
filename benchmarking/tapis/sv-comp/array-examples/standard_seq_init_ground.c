int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int i;
  i = 1;
  a[0] = 7;
  while(i < SIZE) {
    a[i] = a[i - 1] + 1;
    i = i + 1;
  }

  for(int x = 1; x < SIZE; x++) {
    assert(a[x] >= a[x - 1]);
  }
  return 0;
}
