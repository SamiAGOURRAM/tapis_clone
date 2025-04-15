//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  unsigned int start;
  unsigned int end;
  assume(N > 0 && 0 <= start && start <= end && end < N);
  int array[N];
  //*-- computation
  int pivot = array[end];
  int i = start - 1;

  for(unsigned int j = start; j <= end - 1; j++) {
    if(array[j] <= pivot) {
      i++;
      int tmp = array[j];
      array[j] = array[i];
      array[i] = tmp;
    }
  }
  i = i + 1;
  int tmp1 = array[i];
  array[i] = array[end];
  array[end] = tmp1;
  unsigned int pi = i;
  //*-- specification
  assert(start <= pi && pi <= end);
  for(unsigned int k = start; k <= pi; k++) {
    assert(array[k] <= array[pi]);
  }
  for(unsigned int l = pi; l <= end; l++) {
    assert(array[l] >= array[pi]);
  }

  return 0;
}
