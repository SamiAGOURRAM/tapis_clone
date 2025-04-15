extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_doub_access_init_const.c", 3, "reach_error"); }

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
  int N = __VERIFIER_nondet_int();
  assume_abort_if_not(N >= 0);
  int a[2 * N + 2];

  for(int i = 0; i <= N; i++) {
    a[2 * i] = 0;
    a[2 * i + 1] = 0;
  }

  for(int k = 0; k <= 2 * N; k++) {
    __VERIFIER_assert(a[k] >= 0);
  }
  return 0;
}
