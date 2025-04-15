//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void array_quick_sort(int array[], unsigned int start, unsigned int end) {
  if(start < end) {
    unsigned int pi;
    assume(start <= pi && pi <= end);
    for(unsigned int k = start; k <= pi; k++) {
      assume(array[k] <= array[pi]);
    }
    for(unsigned int k = pi + 1; k <= end; k++) {
      assume(array[k] >= array[pi]);
    }

    array_quick_sort(array, start, pi - 1);
    array_quick_sort(array, pi + 1, end);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  array_quick_sort(array, 0, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
