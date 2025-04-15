int main() {
  int CELLCOUNT_2;
  assume(2 * CELLCOUNT_2 > 1);

  int volArray[2 * CELLCOUNT_2];

  int i;
  for(i = 1; i <= CELLCOUNT_2; i++) {
    if(3 >= 2) {
      volArray[i * 2 - 2] = 3;
    } else {
      volArray[i * 2 - 2] = 0;
    }
    volArray[i * 2 - 1] = volArray[i * 2 - 1];
  }

  for(i = 1; i <= CELLCOUNT_2; i++) {
    if(1 >= 2) {
      volArray[i * 2 - 1] = 1;
    } else {
      volArray[i * 2 - 1] = 0;
    }
    volArray[i * 2 - 2] = volArray[i * 2 - 2];
  }

  for(int k = 0; k < 2 * CELLCOUNT_2; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}

