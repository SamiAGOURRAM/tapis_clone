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
  while(i < N) {
    array[i] = i;
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] == k);
  }

  return 0;
}
