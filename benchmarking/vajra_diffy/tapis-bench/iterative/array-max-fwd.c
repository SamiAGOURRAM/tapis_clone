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
  int array[N];
  for(int j = 0; j < N; j++) {
    array[j] = __VERIFIER_nondet_int();
  }
  //*-- computation
  int max[1];
  max[0] = array[0];
  int i = 0;
  while(i < N) {
    if(max[0] < array[i]) {
      max[0] = array[i];
    }
    i++;
  }
  //*-- specification
  int x;
  for(x = 0; x < N; x++) {
    __VERIFIER_assert(array[x] <= max[0]);
  }

  return 0;
}
