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
  int j = N;
  while(j > 0) {
    array1[j - 1] = array2[N - j];
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array1[k] == array2[N - k - 1]);
  }

  return 0;
}
