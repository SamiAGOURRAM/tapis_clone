extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array-argmax-both.c", 3, "reach_error"); }

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
  int SIZE = __VERIFIER_nondet_int();
  assume_abort_if_not(SIZE > 0);
  int a[SIZE];
  int b[SIZE];

  int i;
  for(i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = i;
  }

  for(i = 0; i < SIZE; i++) {
    int bo = __VERIFIER_nondet_int();
    if(bo != 0) {
      int k = __VERIFIER_nondet_int();
      a[i] = k;
      b[i] = k * k;
    }
  }

  for(int l = 0; l < SIZE; l++) {
    __VERIFIER_assert(a[l] == b[l] || b[l] == a[l] * a[l]);
  }
}

