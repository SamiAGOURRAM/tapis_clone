//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  bool swapped = true;
  while(swapped) {
    swapped = false;
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
  }
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
