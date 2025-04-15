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
  int i = 0;
  while(i < N) {
    a[i] = 42;
    i = i + 1;
  }
  i = 0;
  while(i < N) {
    a[i] = 43;
    i = i + 1;
  }

  int x;
  for(x = 0; x < N; x++) {
    __VERIFIER_assert(a[x] == 43);
  }
  return 0;
}
