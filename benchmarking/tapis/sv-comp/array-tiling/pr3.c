int main() {
  int CELLCOUNT_3;
  assume(3 * CELLCOUNT_3 > 1);

  int MINVAL;
  int volArray[3 * CELLCOUNT_3];

  for(int i = 1; i <= CELLCOUNT_3; i++) {
    if(7 >= MINVAL) {
      volArray[i * 3 - 3] = 7;
    } else {
      volArray[i * 3 - 3] = 0;
    }

    if(3 >= MINVAL) {
      volArray[i * 3 - 2] = 3;
    } else {
      volArray[i * 3 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 3 - 1] = 1;
    } else {
      volArray[i * 3 - 1] = 0;
    }
  }

  for(int k = 0; k < 3 * CELLCOUNT_3; k++) {
    assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
