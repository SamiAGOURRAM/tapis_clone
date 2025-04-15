//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-insert-first-rec.c", 3, "reach_error"); }

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

void array_insert_first(int array[], int i, int N) {
  if(i < N) {
    if(array[i - 1] > array[i]) {
      int tmp = array[i - 1];
      array[i - 1] = array[i];
      array[i] = tmp;
      array_insert_first(array, i + 1, N);
    }
  }
}

int main() {

  //*-- precondition
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  int array[N];
  for(int k = 0; k < N; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  for(int k = 1; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      assume_abort_if_not(array[k] <= array[l]);
    }
  }

  //*-- computation
  array_insert_first(array, 1, N);

  //*-- specification
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      __VERIFIER_assert(array[k] <= array[l]);
    }
  }

  return 0;
}
