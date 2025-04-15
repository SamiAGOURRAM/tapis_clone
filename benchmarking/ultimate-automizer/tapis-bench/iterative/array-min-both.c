//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-min-both.c", 3, "reach_error"); }

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

int main() {

  //*-- precondition
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  int array[N];
  //*-- computation
  int min = array[0];
  int i = 0;
  int j = N;
  while(i < N && j > 0 && i <= j) {
    if(min > array[i]) {
      min = array[i];
    }
    if(min > array[j - 1]) {
      min = array[j - 1];
    }
    i++;
    j--;
  }
  //*-- specification
  for(int k = 0; k < N; k++) {
    __VERIFIER_assert(array[k] >= min);
  }

  return 0;
}
