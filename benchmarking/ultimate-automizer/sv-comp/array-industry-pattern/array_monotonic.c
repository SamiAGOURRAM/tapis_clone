extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_monotonic.c", 3, "reach_error"); }

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

  for(int i = 0; i < SIZE; i = i + 2) {
    a[i] = __VERIFIER_nondet_int();
    if(a[i] == 10) {
      b[i] = 20;
    }
  }

  for(int j = 0; j < SIZE; j = j + 2) {
    if(a[j] == 10) {
      __VERIFIER_assert(b[j] == 20);
    }
  }
}

