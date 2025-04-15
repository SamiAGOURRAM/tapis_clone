int main() {
  int CELLCOUNT_5;
  assume(5 * CELLCOUNT_5 > 1);

  int volArray[5 * CELLCOUNT_5];

  for(int i = 1; i <= CELLCOUNT_5; i++) {
    for(int j = 5; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 5 - j] = j;
      } else {
        volArray[i * 5 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 5 * CELLCOUNT_5; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}
