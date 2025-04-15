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
  int src[N];
  int dst[N];
  int i = 0;

  for(i = 0; i < N; i++) {
    src[i] = __VERIFIER_nondet_int();
  }

  i = 0;
  while(src[i] != 0) {
    dst[i] = src[i];
    i = i + 1;
  }

  i = 0;
  while(src[i] != 0) {
    __VERIFIER_assert(dst[i] == src[i]);
    i = i + 1;
  }
  return 0;
}

