int main() {
  int CELLCOUNT_4;
  assume(4 * CELLCOUNT_4 > 1);

  int volArray[4 * CELLCOUNT_4];

  for(int i = 1; i <= CELLCOUNT_4; i++) {
    for(int j = 4; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 4 - j] = j;
      } else {
        volArray[i * 4 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 4 * CELLCOUNT_4; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}
