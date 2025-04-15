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
  unsigned int i = 0;
  while(i < N) {
    if(array[i] == v) {
      idx = i;
    }
    i++;
  }
  //*-- specification
  if(idx != -1) {
    assert(v == array[idx]);
  }

  return 0;
}
