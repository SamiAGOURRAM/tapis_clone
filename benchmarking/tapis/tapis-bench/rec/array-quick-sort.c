//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int lomuto_array_partition(int array[], unsigned int start, unsigned int end) {
  int pivot = array[end];
  int i = start - 1;

  unsigned int j = start;
  while(j <= end - 1) {
    if(array[j] <= pivot) {
      i++;
      int tmp = array[j];
      array[j] = array[i];
      array[i] = tmp;
    }
    j++;
  }
  i++;
  int tmp1 = array[i];
  array[i] = array[end];
  array[end] = tmp1;
  return i;
}

void array_quick_sort(int array[], unsigned int start, unsigned int end) {
  if(start < end) {
    int pi = lomuto_array_partition(array, start, end);

    array_quick_sort(array, start, pi - 1);
    array_quick_sort(array, pi + 1, end);
  }
}

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array[N];
  //*-- computation
  array_quick_sort(array, 0, N - 1);
  //*-- specification
  for(unsigned int k = 0; k < N - 1; k++) {
    for(unsigned int l = k + 1; l < N; l++) {
      assert(array[k] <= array[l]);
    }
  }

  return 0;
}
