//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_min(int array[], int j) {
  if(j == 0) {
    return array[0];
  }
  int min = rec_array_min(array, j - 1);
  if(array[j] <= min) {
    return array[j];
  }
  return min;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int min = rec_array_min(array, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= min);
  }

  return 0;
}
