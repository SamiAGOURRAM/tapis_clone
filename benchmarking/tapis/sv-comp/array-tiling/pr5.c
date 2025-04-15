int main() {
  int CELLCOUNT_5;
  assert(5 * CELLCOUNT_5 > 1);

  int MINVAL;
  int volArray[5 * CELLCOUNT_5];

  for(int i = 1; i <= CELLCOUNT_5; i++) {
    if(2 >= MINVAL) {
      volArray[i * 5 - 5] = 2;
    } else {
      volArray[i * 5 - 5] = 0;
    }

    if(5 >= MINVAL) {
      volArray[i * 5 - 4] = 5;
    } else {
      volArray[i * 5 - 4] = 0;
    }

    if(7 >= MINVAL) {
      volArray[i * 5 - 3] = 7;
    } else {
      volArray[i * 5 - 3] = 0;
    }

    if(3 >= MINVAL) {
      volArray[i * 5 - 2] = 3;
    } else {
      volArray[i * 5 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 5 - 1] = 1;
    } else {
      volArray[i * 5 - 1] = 0;
    }
  }

  for(int k = 0; k < 5 * CELLCOUNT_5; k++) {
    assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
