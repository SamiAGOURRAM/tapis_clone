//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void array_insert_last(int array[], unsigned int N) {
  if(N >= 1) {
    if(array[N - 1] > array[N]) {
      int tmp = array[N - 1];
      array[N - 1] = array[N];
      array[N] = tmp;
      array_insert_last(array, N - 1);
    }
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  for(unsigned int k = 0; k < N - 2; k++) {
    for(unsigned int l = k + 1; l < N - 1; l++) {
      assume(array[k] <= array[l]);
    }
  }

  //*-- computation
  array_insert_last(array, N - 1);

  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
