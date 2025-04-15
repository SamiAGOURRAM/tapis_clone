extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "standard_compare_ground.c", 3, "reach_error"); }

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
  int b[SIZE];

  for(int j = 0; j < SIZE; j++) {
    a[j] = __VERIFIER_nondet_int();
    b[j] = __VERIFIER_nondet_int();
  }

  int i = 0;
  int rv = 1;
  while(i < SIZE) {
    if(a[i] != b[i]) {
      rv = 0;
    }
    i = i + 1;
  }

  if(rv) {
    int x;
    for(x = 0; x < SIZE; x++) {
      __VERIFIER_assert(a[x] == b[x]);
    }
  }
  return 0;
}
