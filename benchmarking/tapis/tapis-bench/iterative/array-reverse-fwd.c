//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array1[N];
  int array2[N];
  //*-- computation
  unsigned int i = 0;
  while(i < N) {
    array1[i] = array2[N - i - 1];
    i = i + 1;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array1[k] == array2[N - k - 1]);
  }

  return 0;
}
