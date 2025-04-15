//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  unsigned int L;
  assume(N > 0);
  assume(L == 2 * N);
  int array1[N];
  int array2[N];
  int array3[L];
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assume(array1[k] <= array1[l]);
    }
  }
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assume(array2[k] <= array2[l]);
    }
  }
  //*-- computation
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;
  while(i < L) {
    if(j == N) {
      array3[i] = array2[k];
      k++;
    } else if(k == N) {
      array3[i] = array1[j];
      j++;
    } else {
      if(array1[j] <= array2[k]) {
        array3[i] = array1[j];
        j++;
      } else {
        array3[i] = array2[k];
        k++;
      }
    }
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < L - 1; k++) {
    for(unsigned int l = k + 1; l < L; l++) {
      assert(array3[k] <= array3[l]);
    }
  }

  return 0;
}
