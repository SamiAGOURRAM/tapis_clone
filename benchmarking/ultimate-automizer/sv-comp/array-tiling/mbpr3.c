extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "mbpr3.c", 3, "reach_error"); }

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
  int volArray[3 * CELLCOUNT_3];

  int i;
  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(7 >= 2) {
      volArray[i * 3 - 3] = 7;
    } else {
      volArray[i * 3 - 3] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
  }

  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(3 >= 2) {
      volArray[i * 3 - 2] = 3;
    } else {
      volArray[i * 3 - 2] = 0;
    }
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
  }

  for(i = 1; i <= CELLCOUNT_3; i++) {
    if(1 >= 2) {
      volArray[i * 3 - 1] = 1;
    } else {
      volArray[i * 3 - 1] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
  }

  for(int k = 0; k < 3 * CELLCOUNT_3; k++) {
    __VERIFIER_assert(volArray[k] >= 2 || volArray[k] == 0);
  }
  return 1;
}

