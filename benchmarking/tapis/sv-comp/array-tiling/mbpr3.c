int main() {
  int CELLCOUNT_3;
  assume(3 * CELLCOUNT_3 > 1);
  int volArray[3 * CELLCOUNT_3];

  int i;
  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(7 >= 2) {
      volArray[i * 3 - 3] = 7;
    } else {
      volArray[i * 3 - 3] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
  }

  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(3 >= 2) {
      volArray[i * 3 - 2] = 3;
    } else {
      volArray[i * 3 - 2] = 0;
    }
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
  }

  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(1 >= 2) {
      volArray[i * 3 - 1] = 1;
    } else {
      volArray[i * 3 - 1] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
  }

  for(int k = 0; k < 3 * CELLCOUNT_3; k++) {
    assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}

