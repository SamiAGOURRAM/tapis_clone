//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_init_0_left(int array[], unsigned int i, int j, int N);

void rec_init_0_right(int array[], unsigned int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    array[j - 1] = 0;
    rec_init_0_left(array, i, j - 1, N);
  }
}

void rec_init_0_left(int array[], unsigned int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    array[i] = 0;
    rec_init_0_right(array, i + 1, j, N);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  rec_init_0_left(array, 0, N, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array[k] == 0);
  }

  return 0;

}
