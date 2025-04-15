extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "nr3.c", 3, "reach_error"); }

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
  int CELLCOUNT_3 = __VERIFIER_nondet_int();
  assume_abort_if_not(3 * CELLCOUNT_3 > 1);

  int volArray[CELLCOUNT_3];

  for(int i = 1; i <= CELLCOUNT_3; i++) {
    for(int j = 3; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 3 - j] = j;
      } else {
        volArray[i * 3 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 3 * CELLCOUNT_3; k++) {
    __VERIFIER_assert(volArray[k] >= 2 || volArray[k] == 0);
  }

  return 1;
}
