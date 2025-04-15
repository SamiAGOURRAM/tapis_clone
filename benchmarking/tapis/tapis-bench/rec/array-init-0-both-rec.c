//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_init_0(int array[], unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    array[i] = 0;
    array[j - 1] = 0;
    rec_init_0(array, i + 1, j - 1, N);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  rec_init_0(array, 0, N, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] == 0);
  }

  return 0;

}
