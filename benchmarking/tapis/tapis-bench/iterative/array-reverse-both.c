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
  int j = N;
  while(i < N && j > 0 && i <= j) {
    array1[i] = array2[N - i - 1];
    array1[j - 1] = array2[N - j];
    i++;
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array1[k] == array2[N - k - 1]);
  }

  return 0;
}
