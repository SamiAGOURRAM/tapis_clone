//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-partition-ver-lomuto.c", 3, "reach_error"); }

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
  int start = __VERIFIER_nondet_int();
  int end = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0 && 0 <= start && start <= end && end < N);
  int array[N];
  for(int k = 0; k < N; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  //*-- computation
  int pivot = array[end];
  int i = start - 1;

  for(int j = start; j <= end - 1; j++) {
    if(array[j] <= pivot) {
      i++;
      int tmp = array[j];
      array[j] = array[i];
      array[i] = tmp;
    }
  }
  i = i + 1;
  int tmp1 = array[i];
  array[i] = array[end];
  array[end] = tmp1;
  int pi = i;
  //*-- specification
  __VERIFIER_assert(start <= pi && pi <= end);
  for(int k = start; k <= pi; k++) {
    __VERIFIER_assert(array[k] <= array[pi]);
  }
  for(int l = pi; l <= end; l++) {
    __VERIFIER_assert(array[l] >= array[pi]);
  }

  return 0;
}
