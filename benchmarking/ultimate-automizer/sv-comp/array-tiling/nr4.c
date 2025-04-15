extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "nr4.c", 3, "reach_error"); }

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
  int CELLCOUNT_4 = __VERIFIER_nondet_int();
  assume_abort_if_not(4 * CELLCOUNT_4 > 1);

  int volArray[4 * CELLCOUNT_4];

  for(int i = 1; i <= CELLCOUNT_4; i++) {
    for(int j = 4; j >= 1; j--) {
      if(j >= 2) {
        volArray[i * 4 - j] = j;
      } else {
        volArray[i * 4 - j] = 0;
      }
    }
  }

  for(int k = 0; k < 4 * CELLCOUNT_4; k++) {
    __VERIFIER_assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}
