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
  int aa[N];
  int a = 0;

  for(int i = 0; i < N; i++) {
    aa[i] = __VERIFIER_nondet_int();
  }

  while(aa[a] >= 0) {
    a++;
  }

  int x;
  for(x = 0; x < a; x++) {
    __VERIFIER_assert(aa[x] >= 0);
  }
  return 0;
}


