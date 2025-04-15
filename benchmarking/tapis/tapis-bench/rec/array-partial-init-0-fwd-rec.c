//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_partial_init_0(int array[], unsigned int i, unsigned int end) {
  if(i < end) {
    array[i] = 0;
    rec_partial_init_0(array, i + 1, end);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  unsigned int begin;
  unsigned int end;
  assume(0 <= begin && begin <= end && end <= N);
  int array[N];
  //*-- computation
  rec_partial_init_0(array, begin, end);
  //*-- specification
  for(unsigned int k = begin; k < end; k++) {
    assert(array[k] == 0);
  }

  return 0;
}
