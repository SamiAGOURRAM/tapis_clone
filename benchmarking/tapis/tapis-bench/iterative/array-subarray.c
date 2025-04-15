//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int M;
  unsigned int N;
  assume(N > 0 && M > 0 && N <= M);
  int array[M];
  int subarray[N];
  //*-- computation
  int idx = -1;
  unsigned int i = 0;
  while(i < M) {
    if(M - i >= N) {
      bool is_sub = true;
      unsigned int k = 0;
      while(is_sub == true && k < N) {
        if(array[i + k] != subarray[k]) {
          is_sub = false;
        }
        k++;
      }
      if(is_sub == true) {
        idx = i;
      }
    }
    i++;
  }
  //*-- specification
  if(idx != -1) {
    assert(idx >= 0);
    for(unsigned int k = 0; k < N; k++) {
      assert(subarray[k] == array[idx + k]);
    }
  }

}
