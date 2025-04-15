extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "standard_compareModified_ground.c", 3, "reach_error"); }

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
  int i = 0;
  int c[SIZE];
  int rv = 1;

  for(int j = 0; j < SIZE; j++) {
    a[j] = __VERIFIER_nondet_int();
    b[j] = __VERIFIER_nondet_int();
  }

  while(i < SIZE) {
    if(a[i] != b[i]) {
      rv = 0;
    }
    c[i] = a[i];
    i = i + 1;
  }

  int x;
  if(rv) {
    for(x = 0; x < SIZE; x++) {
      __VERIFIER_assert(a[x] == b[x]);
    }
  }

  for(x = 0; x < SIZE; x++) {
    __VERIFIER_assert(a[x] == c[x]);
  }
  return 0;
}
