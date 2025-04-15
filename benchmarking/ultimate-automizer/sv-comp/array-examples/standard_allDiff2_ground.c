extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "standard_allDiff2_ground.c", 3, "reach_error"); }

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
  int i;
  int r = 1;

  for(i = 0; i < N; i++) {
    a[i] = __VERIFIER_nondet_int();
  }

  for(i = 1; i < N && r; i++) {
    int j;
    for(j = i - 1; j >= 0 && r; j--) {
      if(a[i] == a[j]) {
        r = 1;
      }
    }
  }

  if(r) {
    int x;
    int y;
    for(x = 0; x < N; x++) {
      for(y = x + 1; y < N; y++) {
        __VERIFIER_assert(a[x] != a[y]);
      }
    }
  }
  return 0;
}
