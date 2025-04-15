//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmin_left(int array[], unsigned int i, int j, unsigned int N);

unsigned int rec_array_argmin_right(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmin = rec_array_argmin_left(array, i, j - 1, N);
    if(array[j] < array[argmin]) {
      return j;
    }
    return argmin;
  }
  return j;
}

unsigned int rec_array_argmin_left(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmin = rec_array_argmin_right(array, i + 1, j, N);
    if(array[i] < array[argmin]) {
      return i;
    }
    return argmin;
  }
  return i;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmin = rec_array_argmin_left(array, 0, N - 1, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
