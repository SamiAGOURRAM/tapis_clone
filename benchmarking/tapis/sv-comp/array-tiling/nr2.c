int main() {
  int CELLCOUNT_2;
  assume(2 * CELLCOUNT_2 > 1);

  int volArray[2 * CELLCOUNT_2];

  for(int i = 1; i <= CELLCOUNT_2; i++) {
    for(int j = 2; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 2 - j] = j;
      } else {
        volArray[i * 2 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 2 * CELLCOUNT_2; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}
