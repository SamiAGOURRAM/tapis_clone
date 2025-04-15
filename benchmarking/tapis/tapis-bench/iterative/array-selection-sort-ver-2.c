//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int partial_array_argmin(int array[], unsigned int start, unsigned int end) {
  unsigned int i = start;
  unsigned int argmin = start;
  while(i < end) {
    if(array[i] < array[argmin]) {
      argmin = i;
    }
    i = i + 1;
  }
  return argmin;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int i = 0;
  while(i < N - 1) {
    unsigned int jmin = partial_array_argmin(array, i, N);
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
