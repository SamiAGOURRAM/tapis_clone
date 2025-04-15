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
  int SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  int i;
  i = 1;
  a[0] = 7;
  while(i < SIZE) {
    a[i] = a[i - 1] + 1;
    i = i + 1;
  }

  int x;
  for(x = 1; x < SIZE; x++) {
    __VERIFIER_assert(a[x] >= a[x - 1]);
  }
  return 0;
}
