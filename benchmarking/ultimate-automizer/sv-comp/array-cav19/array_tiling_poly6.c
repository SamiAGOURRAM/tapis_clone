extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_tiling_poly6.c", 3, "reach_error"); }

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
  assume_abort_if_not(S > 0);
  int a[S];

  int i;
  for(i = 0; i < S; i++) {
    a[i] = ((i - 1) * (i + 1));
  }

  for(i = 0; i < S; i++) {
    a[i] = a[i] - (i * i);
  }

  for(int k = 0; k < S; k++) {
    __VERIFIER_assert(a[k] == -1);
  }
  return 0;
}

