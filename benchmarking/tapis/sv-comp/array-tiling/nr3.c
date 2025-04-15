int main() {
  int CELLCOUNT_3;
  assume(3 * CELLCOUNT_3 > 1);

  int volArray[CELLCOUNT_3];

  for(int i = 1; i <= CELLCOUNT_3; i++) {
    for(int j = 3; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 3 - j] = j;
      } else {
        volArray[i * 3 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 3 * CELLCOUNT_3; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }

  return 1;
}
