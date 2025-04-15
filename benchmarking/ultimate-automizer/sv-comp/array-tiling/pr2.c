extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "pr2.c", 3, "reach_error"); }

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
  int CELLCOUNT_2 = __VERIFIER_nondet_int();
  assume_abort_if_not(2 * CELLCOUNT_2 > 1);

  int MINVAL;
  int volArray[2 * CELLCOUNT_2];

  for(int i = 1; i <= CELLCOUNT_2; i++) {
    if(3 >= MINVAL) {
      volArray[i * 2 - 2] = 3;
    } else {
      volArray[i * 2 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 2 - 1] = 1;
    } else {
      volArray[i * 2 - 1] = 0;
    }
  }

  for(int k = 0; k < 2 * CELLCOUNT_2; k++) {
    __VERIFIER_assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
