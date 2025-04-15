int main() {
  int CELLCOUNT_4;
  assume(4 * CELLCOUNT_4 > 1);

  int volArray[4 * CELLCOUNT_4];

  for(int i = 1; i <= CELLCOUNT_4; i++) {
    if(5 >= 2) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }
    volArray[i * 4 - 3] = volArray[i * 4 - 3];
    volArray[i * 4 - 2] = volArray[i * 4 - 2];
    volArray[i * 4 - 1] = volArray[i * 4 - 1];
  }

  for(int j = 1; j <= CELLCOUNT_4; j++) {
    if(7 >= 2) {
      volArray[j * 4 - 3] = 7;
    } else {
      volArray[j * 4 - 3] = 0;
    }
    volArray[j * 4 - 4] = volArray[j * 4 - 4];
    volArray[j * 4 - 2] = volArray[j * 4 - 2];
    volArray[j * 4 - 1] = volArray[j * 4 - 1];
  }

  for(int k = 1; k <= CELLCOUNT_4; k++) {
    if(3 >= 2) {
      volArray[k * 4 - 2] = 3;
    } else {
      volArray[k * 4 - 2] = 0;
    }
    volArray[k * 4 - 4] = volArray[k * 4 - 4];
    volArray[k * 4 - 3] = volArray[k * 4 - 3];
    volArray[k * 4 - 1] = volArray[k * 4 - 1];
  }

  for(int l = 1; l <= CELLCOUNT_4; l++) {
    if(1 >= 2) {
      volArray[l * 4 - 1] = 1;
    } else {
      volArray[l * 4 - 1] = 0;
    }
    volArray[l * 4 - 4] = volArray[l * 4 - 4];
    volArray[l * 4 - 3] = volArray[l * 4 - 3];
    volArray[l * 4 - 2] = volArray[l * 4 - 2];
  }

  for(int m = 0; m < 4 * CELLCOUNT_4; m++) {
    assert(volArray[m] >= 2 || volArray[m] == 0);
  }

  return 1;
}

