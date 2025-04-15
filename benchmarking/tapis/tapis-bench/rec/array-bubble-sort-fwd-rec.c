//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_array_bubble_sort(int array[], unsigned int N) {
  bool swapped = false;
  unsigned int i = 1;
  while(i < N) {
    if(array[i - 1] > array[i]) {
      int tmp = array[i];
      array[i] = array[i - 1];
      array[i - 1] = tmp;
      swapped = true;
    }
    i++;
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
