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
  unsigned int argmin = N - 1;
  while(j > 0) {
    if(array[argmin] > array[j - 1]) {
      argmin = j - 1;
    }
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
