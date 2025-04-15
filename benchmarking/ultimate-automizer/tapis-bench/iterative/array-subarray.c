//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-subarray.c", 3, "reach_error"); }

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

int main() {

  //*-- precondition
  int M = __VERIFIER_nondet_int();
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0 && M > 0 && N <= M);
  int array[M];
  for(int k = 0; k < M; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  int subarray[N];
  for(int k = 0; k < N; k++) {
    subarray[k] = __VERIFIER_nondet_int();
  }
  //*-- computation
  int idx = -1;
  int i = 0;
  while(i < M) {
    if(M - i >= N) {
      bool is_sub = true;
      int k = 0;
      while(is_sub == true && k < N) {
        if(array[i + k] != subarray[k]) {
          is_sub = false;
        }
        k++;
      }
      if(is_sub == true) {
        idx = i;
      }
    }
    i++;
  }
  //*-- specification
  if(idx != -1) {
    __VERIFIER_assert(idx >= 0);
    for(int k = 0; k < N; k++) {
      __VERIFIER_assert(subarray[k] == array[idx + k]);
    }
  }

}
