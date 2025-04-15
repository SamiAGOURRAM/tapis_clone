//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_min(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int min = rec_array_min(array, i + 1, j - 1, N);
    if(array[i] <= min && array[i] <= array[j]) {
      return array[i];
    }
    if(array[j] <= min && array[j] <= array[i]) {
      return array[j];
    }
    return min;
  }
  return array[j];
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int min = rec_array_min(array, 0, N, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= min);
  }

  return 0;
}
