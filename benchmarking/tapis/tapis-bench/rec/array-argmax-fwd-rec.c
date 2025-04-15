//
// Copyright (c) 2023 Wael-Amine Boutglay
//

unsigned int rec_array_argmax(int array[], unsigned int i, unsigned int N) {
  if(i == N - 1) {
    return i;
  }
  unsigned int argmax = rec_array_argmax(array, i + 1, N);
  if(array[i] >= array[argmax]) {
    return i;
  }
  return argmax;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  unsigned int argmax = rec_array_argmax(array, 0, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] <= array[argmax]);
  }

  return 0;
}
