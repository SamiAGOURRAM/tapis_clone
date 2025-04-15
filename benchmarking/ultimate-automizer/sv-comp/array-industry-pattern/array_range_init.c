extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_range_init.c", 3, "reach_error"); }

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
  int uv = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= uv && uv < SIZE);
  for(int i = 0; i < SIZE; i++) {
    if(i >= 0 && i <= uv) {
      a[i] = 1;
    } else {
      a[i] = 0;
    }
  }


  for(int k = 0; k < SIZE; k++) {
    __VERIFIER_assert(a[k] == 1);

  }

  return 0;
}


