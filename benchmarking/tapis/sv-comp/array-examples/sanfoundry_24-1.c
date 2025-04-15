int main() {
  int SIZE;
  assume(SIZE > 0);
  int array[SIZE];
  int i;
  int num;
  assume(num < SIZE);

  for(i = 0; i < num; i++) {
    if(array[i] % 2 == 0) {
      assert((array[i] % 2) == 0);
    }
  }
  for(i = 0; i < num; i++) {
    if(array[i] % 2 != 0) {
      assert((array[i] % 2) != 0);
    }
  }
  return 0;
}
