int main() {
  int SIZE;
  assume(SIZE > 0);
  int array[SIZE];
  int i;

  int largest = array[0];
  for(i = 1; i < SIZE; i++) {
    if(largest < array[i]) {
      largest = array[i];
    }
  }

  for(int x = 0; x < SIZE; x++) {
    assert(largest >= array[x]);
  }

  return 0;
}
