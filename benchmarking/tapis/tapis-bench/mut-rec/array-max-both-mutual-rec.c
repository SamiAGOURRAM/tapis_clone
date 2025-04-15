//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_max_left(int array[], unsigned int i, int j, unsigned int N);

unsigned int rec_array_max_right(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int max = rec_array_max_left(array, i, j - 1, N);
    if(array[j] > max) {
      return array[j];
    }
    return max;
  }
  return array[j];
}

unsigned int rec_array_max_left(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int max = rec_array_max_right(array, i + 1, j, N);
    if(array[i] > max) {
      return array[i];
    }
    return max;
  }
  return array[i];
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int max = rec_array_max_left(array, 0, N - 1, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
