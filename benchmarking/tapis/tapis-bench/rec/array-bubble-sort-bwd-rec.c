//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_array_bubble_sort(int array[], unsigned int N) {
  bool swapped = false;
  int j = N - 2;
  while(j >= 0) {
    if(array[j] > array[j + 1]) {
      int tmp = array[j];
      array[j] = array[j + 1];
      array[j + 1] = tmp;
      swapped = true;
    }
    j--;
  }
  if(swapped) {
    rec_array_bubble_sort(array, N);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  rec_array_bubble_sort(array, N);
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
