//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-min-bwd-rec.c", 3, "reach_error"); }

extern void abort(void);

void assume_abort_if_not(int cond) {
  if(!cond) { abort(); }
}

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    {
      reach_error();
      abort();
    }
  }
}

extern int __VERIFIER_nondet_int();

int rec_array_min(int array[], int j) {
  if(j == 0) {
    return array[0];
  }
  int min = rec_array_min(array, j - 1);
  if(array[j] <= min) {
    return array[j];
  }
  return min;
}

int main() {

  //*-- precondition
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  int array[N];
  for(int k = 0; k < N; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  //*-- computation
  int min = rec_array_min(array, N - 1);
  //*-- specification
  for(int k = 0; k < N; k++) {
    __VERIFIER_assert(array[k] >= min);
  }

  return 0;
}
