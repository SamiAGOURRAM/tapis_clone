extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "pr4.c", 3, "reach_error"); }

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

  int MINVAL;
  int volArray[4 * CELLCOUNT_4];

  for(int i = 1; i <= CELLCOUNT_4; i++) {
    if(5 >= MINVAL) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }

    if(7 >= MINVAL) {
      volArray[i * 4 - 3] = 7;
    } else {
      volArray[i * 4 - 3] = 0;
    }

    if(3 >= MINVAL) {
      volArray[i * 4 - 2] = 3;
    } else {
      volArray[i * 4 - 2] = 0;
    }

    if(1 >= MINVAL) {
      volArray[i * 4 - 1] = 1;
    } else {
      volArray[i * 4 - 1] = 0;
    }
  }

  for(int k = 0; k < 4 * CELLCOUNT_4; k++) {
    __VERIFIER_assert(volArray[k] >= MINVAL || volArray[k] == 0);
  }
  return 1;
}
