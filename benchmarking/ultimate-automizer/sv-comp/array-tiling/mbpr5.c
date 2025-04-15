extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "mbpr5.c", 3, "reach_error"); }

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
    if(8 >= 2) {
      volArray[i * 5 - 5] = 8;
    } else {
      volArray[i * 5 - 5] = 0;
    }
    volArray[i * 5 - 4] = volArray[i * 5 - 4];
    volArray[i * 5 - 3] = volArray[i * 5 - 3];
    volArray[i * 5 - 2] = volArray[i * 5 - 2];
    volArray[i * 5 - 1] = volArray[i * 5 - 1];
  }

  for(int j = 1; j <= CELLCOUNT_5; j++) {
    if(5 >= 2) {
      volArray[j * 5 - 4] = 5;
    } else {
      volArray[j * 5 - 4] = 0;
    }
    volArray[j * 5 - 5] = volArray[j * 5 - 5];
    volArray[j * 5 - 3] = volArray[j * 5 - 3];
    volArray[j * 5 - 2] = volArray[j * 5 - 2];
    volArray[j * 5 - 1] = volArray[j * 5 - 1];
  }

  for(int k = 1; k <= CELLCOUNT_5; k++) {
    if(7 >= 2) {
      volArray[k * 5 - 3] = 7;
    } else {
      volArray[k * 5 - 3] = 0;
    }
    volArray[k * 5 - 5] = volArray[k * 5 - 5];
    volArray[k * 5 - 4] = volArray[k * 5 - 4];
    volArray[k * 5 - 2] = volArray[k * 5 - 2];
    volArray[k * 5 - 1] = volArray[k * 5 - 1];
  }

  for(int l = 1; l <= CELLCOUNT_5; l++) {
    if(3 >= 2) {
      volArray[l * 5 - 2] = 3;
    } else {
      volArray[l * 5 - 2] = 0;
    }
    volArray[l * 5 - 5] = volArray[l * 5 - 5];
    volArray[l * 5 - 4] = volArray[l * 5 - 4];
    volArray[l * 5 - 3] = volArray[l * 5 - 3];
    volArray[l * 5 - 1] = volArray[l * 5 - 1];
  }

  for(int m = 1; m <= CELLCOUNT_5; m++) {
    if(1 >= 2) {
      volArray[m * 5 - 1] = 1;
    } else {
      volArray[m * 5 - 1] = 0;
    }
    volArray[m * 5 - 5] = volArray[m * 5 - 5];
    volArray[m * 5 - 4] = volArray[m * 5 - 4];
    volArray[m * 5 - 3] = volArray[m * 5 - 3];
    volArray[m * 5 - 2] = volArray[m * 5 - 2];
  }

  for(int n = 0; n < 5 * CELLCOUNT_5; n++) {
    __VERIFIER_assert(volArray[n] >= 2 || volArray[n] == 0);
  }

  return 1;
}

