//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int i = 0;
  while(i < N - 1) {
    unsigned int jmin = i;
    unsigned int j = i + 1;
    while(j < N) {
      if(array[j] < array[jmin]) {
        jmin = j;
      }
      j++;
    }
    if(jmin != i) {
      int tmp = array[jmin];
      array[jmin] = array[i];
      array[i] = tmp;
    }
    i++;
  }
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
