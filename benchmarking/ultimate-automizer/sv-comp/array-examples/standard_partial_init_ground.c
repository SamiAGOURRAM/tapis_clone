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
  int A[N];
  int B[N];
  int C[N];
  int i;
  int j = 0;

  for(i = 0; i < N; i++) {
    A[i] = __VERIFIER_nondet_int();
    B[i] = __VERIFIER_nondet_int();
  }

  for(i = 0; i < N; i++) {
    if(A[i] == B[i]) {
      C[j] = i;
      j = j + 1;
    }
  }


  int x;
  for(x = 0; x < j; x++) {
    __VERIFIER_assert(C[x] <= x + i - j);
  }
  for(x = 0; x < j; x++) {
    __VERIFIER_assert(C[x] >= x);
  }
  return 0;
}
