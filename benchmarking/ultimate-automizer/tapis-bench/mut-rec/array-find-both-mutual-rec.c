//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-find-both-mutual-rec.c", 3, "reach_error"); }

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

int rec_array_find_left(int array[], int v, int i, int j, int N);

int rec_array_find_right(int array[], int v, int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    if(array[j - 1] == v) {
      return j - 1;
    }
    return rec_array_find_left(array, v, i, j - 1, N);
  }
  return -1;
}

int rec_array_find_left(int array[], int v, int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    if(array[i] == v) {
      return i;
    }
    return rec_array_find_right(array, v, i + 1, j, N);
  }
  return -1;
}

int main() {

  //*-- precondition
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N > 0);
  int array[N];
  for(int k = 0; k < N; k++) {
    array[k] = __VERIFIER_nondet_int();
  }
  int v = __VERIFIER_nondet_int();
  //*-- computation
  int idx = rec_array_find_left(array, v, 0, N, N);
  //*-- specification
  if(idx != -1) {
    __VERIFIER_assert(v == array[idx]);
  }

  return 0;

}
