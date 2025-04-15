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
  int j = N;
  while(i < N && j > 0 && i <= j) {
    if(max < array[i]) {
      max = array[i];
    }
    if(max < array[j - 1]) {
      max = array[j - 1];
    }
    i++;
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= max);
  }

  return 0;
}
