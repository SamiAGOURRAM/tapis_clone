int main() {
  int CELLCOUNT_2;
  assume(2 * CELLCOUNT_2 > 1);

  int MINVAL;
  int volArray[2 * CELLCOUNT_2];

  for(int i = 1; i <= CELLCOUNT_2; i++) {
    if(3 >= MINVAL) {
      volArray[i * 2 - 2] = 3;
    } else {
      volArray[i * 2 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 2 - 1] = 1;
    } else {
      volArray[i * 2 - 1] = 0;
    }
  }

  for(int k = 0; k < 2 * CELLCOUNT_2; k++) {
    assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
