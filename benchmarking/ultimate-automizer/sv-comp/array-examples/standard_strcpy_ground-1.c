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
  int j = 0;

  while(j < N) {
    src[j] = __VERIFIER_nondet_int();
    j = j + 1;
  }

  while(i < N && src[i] != 0) {
    dst[i] = src[i];
    i = i + 1;
  }

  int x;
  for(x = 0; x < i; x++) {
    __VERIFIER_assert(dst[x] == src[x]);
  }
  return 0;
}

