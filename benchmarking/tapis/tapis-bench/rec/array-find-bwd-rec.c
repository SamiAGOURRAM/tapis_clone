//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_find(int array[], int v, int j) {
  if(j > 0) {
    if(array[j - 1] == v) {
      return j - 1;
    }
    return rec_array_find(array, v, j - 1);
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
  int idx = rec_array_find(array, v, N);
  //*-- specification
  if(idx != -1) {
    assert(v == array[idx]);
  }

  return 0;

}
