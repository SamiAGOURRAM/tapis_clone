//
// Copyright (c) 2023 Wael-Amine Boutglay
//

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
  int x = array[0];
  int i = 1;
  while(i < N && array[i] < x) {
    array[i] = array[i - 1];
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
