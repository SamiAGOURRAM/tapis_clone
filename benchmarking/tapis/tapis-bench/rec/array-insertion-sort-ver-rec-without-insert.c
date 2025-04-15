//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_array_insert_sort(int array[], unsigned int N) {
  if(N > 0) {
    rec_array_insert_sort(array, N - 1);
    for(unsigned int k = 0; k <= N - 1; k++) {
      for(unsigned int l = k + 1; l <= N; l++) {
        assume(array[k] <= array[l]);
      }
    }
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  rec_array_insert_sort(array, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
