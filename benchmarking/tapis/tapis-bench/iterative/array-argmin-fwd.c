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
  unsigned int argmin = 0;
  while(i < N) {
    if(array[argmin] > array[i]) {
      argmin = i;
    }
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
