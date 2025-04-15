//
// Copyright (c) 2023 Wael-Amine Boutglay
//

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
  int x = array[N - 1];
  int j = N - 2;
  while(j >= 0 && array[j] > x) {
    array[j + 1] = array[j];
    j = j - 1;
  }
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
