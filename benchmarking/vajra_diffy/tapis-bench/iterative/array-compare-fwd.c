//
// Copyright (c) 2023 Wael-Amine Boutglay
//

extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    __VERIFIER_error();
  }
}

extern int __VERIFIER_nondet_int();

int N;

int main() {

  //*-- precondition
  N = __VERIFIER_nondet_int();
  int array1[N];
  int array2[N];
  for(int j = 0; j < N; j++) {
    array1[j] = __VERIFIER_nondet_int();
  }
  for(int j = 0; j < N; j++) {
    array2[j] = __VERIFIER_nondet_int();
  }
  //*-- computation
  int equal = 1;
  int i = 0;
  while(i < N) {
    if(array1[i] != array2[i]) {
      equal = 0;
    }
    i++;
  }
  //*-- specification
  int x;
  for(x = 0; x < N; x++) {
    __VERIFIER_assert(equal == 0 || array1[x] == array2[x]);
  }

  return 0;
}
