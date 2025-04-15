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
  int b = 0;
  int c = 0;
  int bb[N];
  int cc[N];

  while(a < N) {
    aa[a] = __VERIFIER_nondet_int();
    if(aa[a] >= 0) {
      bb[b] = aa[a];
      b = b + 1;
    }
    a = a + 1;
  }
  a = 0;
  while(a < N) {
    if(aa[a] >= 0) {
      cc[c] = aa[a];
      c = c + 1;
    }
    a = a + 1;
  }

  int x;
  for(x = 0; x < b; x++) {
    __VERIFIER_assert(bb[x] >= 0);
  }
  for(x = 0; x < c; x++) {
    __VERIFIER_assert(cc[x] < 0);
  }
  return 0;
}


