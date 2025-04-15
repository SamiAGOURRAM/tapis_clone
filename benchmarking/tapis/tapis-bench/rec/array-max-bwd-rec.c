//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_max(int array[], int j) {
  if(j == 0) {
    return array[0];
  }
  int max = rec_array_max(array, j - 1);
  if(array[j] >= max) {
    return array[j];
  }
  return max;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int max = rec_array_max(array, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
