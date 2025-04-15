//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_find(int array[], int v, unsigned int i, unsigned int N) {
  if(i < N) {
    if(array[i] == v) {
      return i;
    }
    return rec_array_find(array, v, i + 1, N);
  }
  return -1;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  int v;
  //*-- computation
  int idx = rec_array_find(array, v, 0, N);
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
