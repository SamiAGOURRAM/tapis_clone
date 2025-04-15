//
// Copyright (c) 2023 Wael-Amine Boutglay
//

void rec_array_copy(int array1[], int array2[], unsigned int j) {
  if(j > 0) {
    array1[j - 1] = array2[j - 1];
    rec_array_copy(array1, array2, j - 1);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array1[N];
  int array2[N];
  //*-- computation
  rec_array_copy(array1, array2, N);
  //*-- specification
  for(unsigned int k = 0; k < N; k++) {
    assert(array1[k] == array2[k]);
  }

  return 0;
}
