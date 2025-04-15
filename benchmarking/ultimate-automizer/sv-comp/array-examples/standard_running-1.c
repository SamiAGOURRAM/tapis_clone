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
  int b[N];
  int i = 0;

  for(i = 0; i < N; i++) {
    a[i] = __VERIFIER_nondet_int();
  }

  i = 0;
  while(i < N) {
    if(a[i] >= 0) b[i] = 1;
    else b[i] = 0;
    i = i + 1;
  }
  int f = 1;
  i = 0;
  while(i < N) {
    if(a[i] >= 0 && !b[i]) f = 0;
    if(a[i] < 0 && !b[i]) f = 0;
    i = i + 1;
  }
  __VERIFIER_assert(f);
  return 0;
}
