//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  unsigned int begin;
  unsigned int end;
  assume(0 <= begin && begin <= end && end <= N);
  int array[N];
  //*-- computation
  unsigned int i = begin;
  while(i < end) {
    array[i] = 0;
    i++;
  }
  //*-- specification
  for(unsigned int k = begin; k < end; k++) {
    assert(array[k] == 0);
  }

  return 0;
}
