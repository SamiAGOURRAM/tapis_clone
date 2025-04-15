//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int j = N;
  while(j > 0) {
    array[j - 1] = j - 1;
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] == k);
  }

  return 0;
}
