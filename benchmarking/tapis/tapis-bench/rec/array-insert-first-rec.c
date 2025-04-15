//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void array_insert_first(int array[], unsigned int i, unsigned int N) {
  if(i < N) {
    if(array[i - 1] > array[i]) {
      int tmp = array[i - 1];
      array[i - 1] = array[i];
      array[i] = tmp;
      array_insert_first(array, i + 1, N);
    }
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  for(unsigned int k = 1; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assume(array[k] <= array[l]);
    }
  }

  //*-- computation
  array_insert_first(array, 1, N);

  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
