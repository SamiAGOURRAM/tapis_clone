int main() {
  int n;
  assume(n > 0);
  int a[n];

  int j;
  assume(j > 0);

  for(int i = 1; i < n; i++) {
    int k;
    assume(k > 0);
    a[i] = i + j + k;
  }

  for(int k = 1; k < n; k++) {
    assert(a[k] >= (k + 2));
  }
  return 0;
}  
