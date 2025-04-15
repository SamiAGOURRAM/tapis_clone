//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmin(int array[], unsigned int i) {
  if(i == 0) {
    return i;
  }
  unsigned int argmin = rec_array_argmin(array, i - 1);
  if(array[i] <= array[argmin]) {
    return i;
  }
  return argmin;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmin = rec_array_argmin(array, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] >= array[argmin]);
  }

  return 0;
}
