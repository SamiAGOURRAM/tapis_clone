extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "nr5.c", 3, "reach_error"); }

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
  int CELLCOUNT_5 = __VERIFIER_nondet_int();
  assume_abort_if_not(5 * CELLCOUNT_5 > 1);

  int volArray[5 * CELLCOUNT_5];

  for(int i = 1; i <= CELLCOUNT_5; i++) {
    for(int j = 5; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 5 - j] = j;
      } else {
        volArray[i * 5 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 5 * CELLCOUNT_5; k++) {
    __VERIFIER_assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}
