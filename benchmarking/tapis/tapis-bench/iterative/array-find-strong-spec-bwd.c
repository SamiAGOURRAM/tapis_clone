//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  int v;
  //*-- computation
  int idx = -1;
  int j = N;
  while(j > 0) {
    if(array[j - 1] == v) {
      idx = j - 1;
    }
    j--;
  }
  //*-- specification
  if(idx != -1) {
    assert(v == array[idx]);
  } else {
    for(unsigned int k = 0; k < N; k++) {
      assert(array[k] != v);
    }
  }

  return 0;
}
