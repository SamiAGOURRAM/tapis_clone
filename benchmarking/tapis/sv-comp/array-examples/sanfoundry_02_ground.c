int main() {
  int MAX;
  assume(MAX > 0);
  int array[MAX];
  int largest1;
  int largest2;
  int temp;

  /*  assume first element of array is the first larges t*/
  largest1 = array[0];
  /*  assume first element of array is the second largest */
  largest2 = array[1];

  if(largest1 < largest2) {
    temp = largest1;
    largest1 = largest2;
    largest2 = temp;
  }
  for(int i = 2; i < MAX; i++) {
    if(array[i] >= largest1) {
      largest2 = largest1;
      largest1 = array[i];
    } else if(array[i] > largest2) {
      largest2 = array[i];
    }
  }

  for(int x = 0; x < MAX; x++) {
    assert(array[x] <= largest1);
  }
  for(int y = 0; y < MAX; y++) {
    assert(array[y] <= largest2 || array[y] == largest1);
  }
  return 0;
}
