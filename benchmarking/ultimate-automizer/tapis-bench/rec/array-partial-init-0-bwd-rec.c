//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-partial-init-0-bwd-rec.c", 3, "reach_error"); }

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

void rec_partial_init_0(int array[], int begin, int j) {
  if(j - 1 >= begin) {
    array[j - 1] = 0;
    rec_partial_init_0(array, begin, j - 1);
  }
}

int main() {

  //*-- precondition
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  int begin = __VERIFIER_nondet_int();
  int end = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= begin && begin <= end && end <= N);
  int array[N];
  for(int k = 0; k < N; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  //*-- computation
  rec_partial_init_0(array, begin, end);
  //*-- specification
  for(int k = begin; k < end; k++) {
    __VERIFIER_assert(array[k] == 0);
  }

  return 0;
}
