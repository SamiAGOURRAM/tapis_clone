//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-selection-sort-ver-2.c", 3, "reach_error"); }

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

int partial_array_argmin(int array[], int start, int end) {
  int i = start;
  int argmin = start;
  while(i < end) {
    if(array[i] < array[argmin]) {
      argmin = i;
    }
    i = i + 1;
  }
  return argmin;
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
  int i = 0;
  while(i < N - 1) {
    int jmin = partial_array_argmin(array, i, N);
    if(jmin != i) {
      int tmp = array[jmin];
      array[jmin] = array[i];
      array[i] = tmp;
    }
    i++;
  }
  //*-- specification
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      __VERIFIER_assert(array[k] <= array[l]);
    }
  }

  return 0;
}
