//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmin(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int argmin = rec_array_argmin(array, i + 1, j - 1, N);
    if(array[i] <= array[argmin] && array[i] <= array[j]) {
      return i;
    }
    if(array[j] <= array[argmin] && array[j] <= array[i]) {
      return j;
    }
    return argmin;
  }
  return j;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmin = rec_array_argmin(array, 0, N - 1, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
