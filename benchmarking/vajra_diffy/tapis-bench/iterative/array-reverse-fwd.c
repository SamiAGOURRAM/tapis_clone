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
    array2[j] = __VERIFIER_nondet_int();
  }
  //*-- computation
  unsigned int i = 0;
  while(i < N) {
    array1[i] = array2[N - i - 1];
    i = i + 1;
  }
  //*-- specification
  int x;
  for(x = 0; x < N; x++) {
    __VERIFIER_assert(array1[x] == array2[N - x - 1]);
  }

  return 0;
}
