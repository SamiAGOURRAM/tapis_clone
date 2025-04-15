//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-merge.c", 3, "reach_error"); }

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
  int L = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  assume_abort_if_not(L == 2 * N);
  int array1[N];
  int array2[N];
  for(int k = 0; k < N; k++) {
    array1[k] = __VERIFIER_nondet_int();
    array2[k] = __VERIFIER_nondet_int();
  }
  int array3[L];
  for(int k = 0; k < L; k++) {
    array3[k] = __VERIFIER_nondet_int();
  }
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      assume_abort_if_not(array1[k] <= array1[l]);
    }
  }
  for(int k = 0; k < N - 1; k++) {
    for(int l = k + 1; l < N; l++) {
      assume_abort_if_not(array2[k] <= array2[l]);
    }
  }
  //*-- computation
  int i = 0;
  int j = 0;
  int k = 0;
  while(i < L) {
    if(j == N) {
      array3[i] = array2[k];
      k++;
    } else if(k == N) {
      array3[i] = array1[j];
      j++;
    } else {
      if(array1[j] <= array2[k]) {
        array3[i] = array1[j];
        j++;
      } else {
        array3[i] = array2[k];
        k++;
      }
    }
    i++;
  }
  //*-- specification
  for(int k = 0; k < L - 1; k++) {
    for(int l = k + 1; l < L; l++) {
      __VERIFIER_assert(array3[k] <= array3[l]);
    }
  }

  return 0;
}
