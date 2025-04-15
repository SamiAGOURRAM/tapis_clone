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

int _strcmp(int src[], int dst[], int N) {
  int i = 0;
  while(i < N) {
    if(dst[i] != src[i]) return 1;
    i = i + 1;
  }
  return 0;
}


int main() {
  int N = __VERIFIER_nondet_int();
  int a[N];
  int b[N];

  for(int i = 0; i < N; i++) {
    a[i] = __VERIFIER_nondet_int();
    b[i] = __VERIFIER_nondet_int();
  }

  int c = _strcmp(a, b, N);

  if(c == 0) {
    int x;
    for(x = 0; x < N; x++) {
      __VERIFIER_assert(a[x] == b[x]);
    }
  }
  return 0;
}
