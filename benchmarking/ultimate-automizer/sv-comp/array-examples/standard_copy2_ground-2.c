extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "standard_copy2_ground-2.c", 3, "reach_error"); }

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
  int a1[N];
  int a2[N];
  int a3[N];

  int a;
  for(a = 0; a < N; a++) {
    a1[a] = __VERIFIER_nondet_int();
  }

  int i;
  for(i = 0; i < N; i++) {
    a2[i] = a1[i];
  }
  for(i = 0; i < N; i++) {
    a3[i] = a2[i];
  }

  int x;
  for(x = 0; x < N; x++) {
    __VERIFIER_assert(a1[x] == a3[x]);
  }
  return 0;
}

