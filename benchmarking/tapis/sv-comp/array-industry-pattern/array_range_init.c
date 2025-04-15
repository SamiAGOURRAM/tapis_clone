int main() {
  int SIZE;
  assume(SIZE > 0);
  int a[SIZE];
  int uv;
  assume(0 <= uv && uv < SIZE);
  for(int i = 0; i < SIZE; i++) {
    if(i >= 0 && i <= uv) {
      a[i] = 1;
    } else {
      a[i] = 0;
    }
  }


  for(int k = 0; k < SIZE; k++) {
    assert(a[k] == 1);

  }

  return 0;
}


