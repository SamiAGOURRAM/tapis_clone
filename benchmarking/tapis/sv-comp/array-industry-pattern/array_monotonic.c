int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int b[SIZE];
  for(int i = 0; i < SIZE; i = i + 2) {
    if(a[i] == 10) {
      b[i] = 20;
    }
  }

  for(int j = 0; j < SIZE; j = j + 2) {
    if(a[j] == 10) {
      assert(b[j] == 20);
    }
  }
}

