//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int rec_array_find_left(int array[], int v, unsigned int i, int j, unsigned int N);

int rec_array_find_right(int array[], int v, unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    if(array[j - 1] == v) {
      return j - 1;
    }
    return rec_array_find_left(array, v, i, j - 1, N);
  }
  return -1;
}

int rec_array_find_left(int array[], int v, unsigned int i, int j, unsigned int N) {
  if(i < N && j > 0 && i <= j) {
    if(array[i] == v) {
      return i;
    }
    return rec_array_find_right(array, v, i + 1, j, N);
  }
  return -1;
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  int v;
  //*-- computation
  int idx = rec_array_find_left(array, v, 0, N, N);
  //*-- specification
  if(idx != -1) {
    assert(v == array[idx]);
  }

  return 0;

}
