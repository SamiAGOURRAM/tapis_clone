//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int i = 0;
  int j = N;
  unsigned int argmin = 0;
  while(i < N && j > 0 && i <= j) {
    if(array[argmin] > array[i]) {
      argmin = i;
    }
    if(array[argmin] > array[j - 1]) {
      argmin = j - 1;
    }
    i++;
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
