extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_tiling_tcpy.c", 3, "reach_error"); }

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
  int S = __VERIFIER_nondet_int();
  assume_abort_if_not(S > 1);
  int a[2 * S];
  int acopy[2 * S];

  for(int i = 0; i < S; i++) {
    acopy[2 * S - (i + 1)] = a[2 * S - (i + 1)];
    acopy[i] = a[i];
  }

  for(int k = 0; k < 2 * S; k++) {
    __VERIFIER_assert(acopy[k] == a[k]);
  }
  return 0;
}

