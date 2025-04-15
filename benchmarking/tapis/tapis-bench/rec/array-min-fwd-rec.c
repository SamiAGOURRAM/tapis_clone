//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_min(int array[], unsigned int i, unsigned int N) {
  if(i == N - 1) {
    return array[i];
  }
  int min = rec_array_min(array, i + 1, N);
  if(array[i] <= min) {
    return array[i];
  }
  return min;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int min = rec_array_min(array, 0, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= min);
  }

  return 0;
}
