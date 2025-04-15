//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-bubble-sort-bwd-rec.c", 3, "reach_error"); }

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

typedef enum {
  true = 1,
  false = 0
} bool;

void rec_array_bubble_sort(int array[], int N) {
  bool swapped = false;
  int j = N - 2;
  while(j >= 0) {
    if(array[j] > array[j + 1]) {
      int tmp = array[j];
      array[j] = array[j + 1];
      array[j + 1] = tmp;
      swapped = true;
    }
    j--;
  }
  if(swapped) {
    rec_array_bubble_sort(array, N);
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
  rec_array_bubble_sort(array, N);
  //*-- specification
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      __VERIFIER_assert(array[k] <= array[l]);
    }
  }

  return 0;
}
