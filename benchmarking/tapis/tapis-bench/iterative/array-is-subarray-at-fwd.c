//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int M;
  unsigned int N;
  unsigned int idx;
  assume(N > 0 && M > 0 && N <= M && 0 <= idx && idx < M);
  int array[M];
  int subarray[N];
  //*-- computation
  bool is_sub = false;
  unsigned int k = 0;
  if(idx + N < M) {
    is_sub = true;
    while(is_sub == true && k < N) {
      if(array[idx + k] != subarray[k]) {
        is_sub = false;
      }
      k++;
    }
  }
  //*-- specification
  if(is_sub == true) {
    for(unsigned int k = 0; k < N; k++) {
      assert(subarray[k] == array[idx + k]);
    }
  }

}
