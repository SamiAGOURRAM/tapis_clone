//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-quick-sort-without-partition.c", 3, "reach_error"); }

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

void array_quick_sort(int array[], int start, int end) {
  if(start < end) {
    int pi = __VERIFIER_nondet_int();
    assume_abort_if_not(start <= pi && pi <= end);
    for(int k = start; k <= pi; k++) {
      assume_abort_if_not(array[k] <= array[pi]);
    }
    for(int k = pi + 1; k <= end; k++) {
      assume_abort_if_not(array[k] >= array[pi]);
    }

    array_quick_sort(array, start, pi - 1);
    array_quick_sort(array, pi + 1, end);
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
  //*-- computation
  array_quick_sort(array, 0, N - 1);
  //*-- specification
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      __VERIFIER_assert(array[k] <= array[l]);
    }
  }

  return 0;
}
