//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  int v;
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assume(array[k] <= array[l]);
    }
  }

  //*-- computation
  unsigned int lo = 0;
  unsigned int hi = N - 1;
  while(hi - lo > 1) {
    unsigned int mid;
    assume(lo <= mid && mid <= hi);
    if(array[mid] < v) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }
  int idx = -1;
  if(array[lo] == v) {
    idx = lo;
  } else if(array[hi] == v) {
    idx = hi;
  }
  //*-- specification
  if(idx != -1) {
    assert(v == array[idx]);
  }

  return 0;
}
