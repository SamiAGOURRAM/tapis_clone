//
// Copyright (c) 2023 Wael-Amine Boutglay
//

int main() {

  //*-- precondition
  unsigned int N;
  assume(N > 0);
  int array1[N];
  int array2[N];
  //*-- computation
  bool equal = true;
  unsigned int i = 0;
  int j = N;
  while(i < N && j > 0 && i <= j) {
    if(array1[j - 1] != array2[j - 1] || array1[i] != array2[i]) {
      equal = false;
    }
    i++;
    j--;
  }
  //*-- specification
  if(equal == true) {
    for(unsigned int k = 0; k < N; k++) {
      assert(array1[k] == array2[k]);
    }
  }

  return 0;
}
