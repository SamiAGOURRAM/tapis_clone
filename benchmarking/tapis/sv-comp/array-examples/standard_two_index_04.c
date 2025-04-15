int main() {
  int size;
  assume(size > 0);
  int a[size];
  int b[size];
  int i = 0;
  int j = 0;

  i = 1;
  while(i < size) {
    a[j] = b[i];
    i = i + 4;
    j = j + 1;
  }

  i = 1;
  j = 0;
  while(i < size) {
    assert(a[j] == b[4 * j + 1]);
    i = i + 4;
    j = j + 1;
  }
  return 0;
}
