//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_max(int array[], unsigned int i, unsigned int N) {
  if(i == N - 1) {
    return array[i];
  }
  int max = rec_array_max(array, i + 1, N);
  if(array[i] >= max) {
    return array[i];
  }
  return max;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int max = rec_array_max(array, 0, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
