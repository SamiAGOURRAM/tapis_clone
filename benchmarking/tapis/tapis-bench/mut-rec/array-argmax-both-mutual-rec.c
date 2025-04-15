//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmax_left(int array[], unsigned int i, int j, unsigned int N);

unsigned int rec_array_argmax_right(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmax = rec_array_argmax_left(array, i, j - 1, N);
    if(array[j] > array[argmax]) {
      return j;
    }
    return argmax;
  }
  return j;
}

unsigned int rec_array_argmax_left(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmax = rec_array_argmax_right(array, i + 1, j, N);
    if(array[i] > array[argmax]) {
      return i;
    }
    return argmax;
  }
  return i;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmax = rec_array_argmax_left(array, 0, N - 1, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= array[argmax]);
  }

  return 0;
}
