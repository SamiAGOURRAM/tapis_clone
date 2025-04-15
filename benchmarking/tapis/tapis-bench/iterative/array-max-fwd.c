//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int max = array[0];
  unsigned int i = 0;
  while(i < N) {
    if(max < array[i]) {
      max = array[i];
    }
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
