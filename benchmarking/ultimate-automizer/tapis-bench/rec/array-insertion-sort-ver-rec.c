//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-insertion-sort-ver-rec.c", 3, "reach_error"); }

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

void rec_array_insert_sort(int array[], int N) {
  if(N > 0) {
    rec_array_insert_sort(array, N - 1);
    int x = array[N];
    int j = N - 1;
    while(j >= 0 && array[j] > x) {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = x;
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
  rec_array_insert_sort(array, N - 1);
  //*-- specification
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      __VERIFIER_assert(array[k] <= array[l]);
    }
  }

  return 0;
}
