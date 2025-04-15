extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_shadowinit.c", 3, "reach_error"); }

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
  if(N > 0) {
    int i, k;
    int a[N];

    i = 0;
    k = 0;
    while(i < N) {
      a[k] = k;
      i = i + 1;
      k = k + 1;
    }

    for(int l = 0; l < N; l++) {
      __VERIFIER_assert(a[l] == l);
    }
  }
  return 0;
}
