int main() {
  int size;
  assume(size > 0);
  int a[size];
  int b[size];
  int i = 0;
  int j = 0;

  i = 0;
  while(i < size) {
    a[j] = b[i];
    i = i + 1;
    j = j + 1;
  }

  i = 0;
  j = 0;
  while(i < size) {
    assert(a[j] == b[j]);
    i = i + 1;
    j = j + 1;
  }
  return 0;
}
