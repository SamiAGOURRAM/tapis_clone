int main() {
  int CELLCOUNT_4;
  assume(4 * CELLCOUNT_4 > 1);

  int MINVAL;
  int volArray[4 * CELLCOUNT_4];

  for(int i = 1; i <= CELLCOUNT_4; i++) {
    if(5 >= MINVAL) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }

    if(7 >= MINVAL) {
      volArray[i * 4 - 3] = 7;
    } else {
      volArray[i * 4 - 3] = 0;
    }

    if(3 >= MINVAL) {
      volArray[i * 4 - 2] = 3;
    } else {
      volArray[i * 4 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 4 - 1] = 1;
    } else {
      volArray[i * 4 - 1] = 0;
    }
  }

  for(int k = 0; k < 4 * CELLCOUNT_4; k++) {
    assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
