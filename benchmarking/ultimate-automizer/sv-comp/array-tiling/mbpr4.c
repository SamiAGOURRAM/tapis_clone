extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "mbpr4.c", 3, "reach_error"); }

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
    if(5 >= 2) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }
    volArray[i * 4 - 3] = volArray[i * 4 - 3];
    volArray[i * 4 - 2] = volArray[i * 4 - 2];
    volArray[i * 4 - 1] = volArray[i * 4 - 1];
  }

  for(int j = 1; j <= CELLCOUNT_4; j++) {
    if(7 >= 2) {
      volArray[j * 4 - 3] = 7;
    } else {
      volArray[j * 4 - 3] = 0;
    }
    volArray[j * 4 - 4] = volArray[j * 4 - 4];
    volArray[j * 4 - 2] = volArray[j * 4 - 2];
    volArray[j * 4 - 1] = volArray[j * 4 - 1];
  }

  for(int k = 1; k <= CELLCOUNT_4; k++) {
    if(3 >= 2) {
      volArray[k * 4 - 2] = 3;
    } else {
      volArray[k * 4 - 2] = 0;
    }
    volArray[k * 4 - 4] = volArray[k * 4 - 4];
    volArray[k * 4 - 3] = volArray[k * 4 - 3];
    volArray[k * 4 - 1] = volArray[k * 4 - 1];
  }

  for(int l = 1; l <= CELLCOUNT_4; l++) {
    if(1 >= 2) {
      volArray[l * 4 - 1] = 1;
    } else {
      volArray[l * 4 - 1] = 0;
    }
    volArray[l * 4 - 4] = volArray[l * 4 - 4];
    volArray[l * 4 - 3] = volArray[l * 4 - 3];
    volArray[l * 4 - 2] = volArray[l * 4 - 2];
  }

  for(int m = 0; m < 4 * CELLCOUNT_4; m++) {
    __VERIFIER_assert(volArray[m] >= 2 || volArray[m] == 0);
  }

  return 1;
}

