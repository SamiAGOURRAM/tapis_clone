//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_max(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int max = rec_array_max(array, i + 1, j - 1, N);
    if(array[i] >= max && array[i] >= array[j]) {
      return array[i];
    }
    if(array[j] >= max && array[j] >= array[i]) {
      return array[j];
    }
    return max;
  }
  return array[j];
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int max = rec_array_max(array, 0, N, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
