//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmax(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmax = rec_array_argmax(array, i + 1, j - 1, N);
    if(array[i] >= array[argmax] && array[i] >= array[j]) {
      return i;
    }
    if(array[j] >= array[argmax] && array[j] >= array[i]) {
      return j;
    }
    return argmax;
  }
  return j;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmax = rec_array_argmax(array, 0, N - 1, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= array[argmax]);
  }

  return 0;
}
