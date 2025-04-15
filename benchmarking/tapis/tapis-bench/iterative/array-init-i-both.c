//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  int i = 0;
  int j = N;
  while(i < N && j > 0 && i <= j) {
    array[i] = i;
    array[j - 1] = j - 1;
    i++;
    j--;
  }
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] == k);
  }

  return 0;
}
