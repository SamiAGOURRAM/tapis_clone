//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int i = 1;
  while(i < N) {
    unsigned int j = i;
    while(j > 0 && array[j - 1] > array[j]) {
      int tmp = array[j];
      array[j] = array[j - 1];
      array[j - 1] = tmp;
      j--;
    }
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
