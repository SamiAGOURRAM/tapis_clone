int main() {
  int n;
  assume(n > 0);
  int pos;
  int element;
  bool found = false;
  int vectorx[n];

  for(int i = 0; i < n && !found; i++) {
    if(vectorx[i] == element) {
      found = true;
      pos = i;
    }
  }
  if(found) {
    for(int j = pos; j < n - 1; j++) {
      vectorx[j] = vectorx[j + 1];
    }
  }

  if(found) {
    for(int k = 0; k < pos; k++) {
      assert(vectorx[k] != element);
    }
  }
  return 0;
}
