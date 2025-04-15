extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "copysome2-1.c", 3, "reach_error"); }

extern void abort(void);

void assume_abort_if_not(int cond) {
  if(!cond) { abort(); }
}

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
  assume_abort_if_not(N > 0);
  int a1[N];
  int a2[N];
  int a3[N];

  int i;
  for(i = 0; i < N; i++) {
    a1[i] = __VERIFIER_nondet_int();
    a2[i] = __VERIFIER_nondet_int();
    a3[i] = __VERIFIER_nondet_int();
  }

  int z = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= z && z < N);

  for(i = 0; i < N; i++) {
    if(i != z)
      a2[i] = a1[i];
  }
  for(i = 0; i < N; i++) {
    if(i != z)
      a3[i] = a2[i];
    else
      a3[i] = a1[i];
  }

  for(int x = 0; x < N; x++) {
    __VERIFIER_assert(a1[x] == a3[x]);
  }
  return 0;
}

