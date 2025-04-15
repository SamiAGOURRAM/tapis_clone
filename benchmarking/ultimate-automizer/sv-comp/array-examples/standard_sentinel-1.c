extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "", 3, "reach_error"); }

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
  int a[N];
  int marker = __VERIFIER_nondet_int();
  int pos = __VERIFIER_nondet_int();

  for(int i = 0; i < N; i++) {
    a[i] = __VERIFIER_nondet_int();
  }

  if(pos >= 0 && pos < N) {
    a[pos] = marker;

    int i = 0;
    while(a[i] != marker) {
      i = i + 1;
    }

    __VERIFIER_assert(i <= pos);
  }
  return 0;
}
