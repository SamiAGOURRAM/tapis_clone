//
// Copyright (c) 2024 Wael-Amine Boutglay
//

extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-max-both-mutual-rec.c", 3, "reach_error"); }

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

int rec_array_max_left(int array[], int i, int j, int N);

int rec_array_max_right(int array[], int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int max = rec_array_max_left(array, i, j - 1, N);
    if(array[j] > max) {
      return array[j];
    }
    return max;
  }
  return array[j];
}

int rec_array_max_left(int array[], int i, int j, int N) {
  if(i < N && j > 0 && i <= j) {
    unsigned int max = rec_array_max_right(array, i + 1, j, N);
    if(array[i] > max) {
      return array[i];
    }
    return max;
  }
  return array[i];
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
  unsigned int max = rec_array_max_left(array, 0, N - 1, N);
  //*-- specification
  for(int k = 0; k < N; k++) {
    __VERIFIER_assert(array[k] <= max);
  }

  return 0;
}
