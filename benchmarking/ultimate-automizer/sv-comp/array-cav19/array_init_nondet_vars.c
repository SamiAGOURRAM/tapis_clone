extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_init_nondet_vars.c", 3, "reach_error"); }

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
  int n = __VERIFIER_nondet_int();
  assume_abort_if_not(n > 0);
  int a[n];

  int j = __VERIFIER_nondet_int();
  assume_abort_if_not(j > 0);

  for(int i = 1; i < n; i++) {
    int k = __VERIFIER_nondet_int();
    assume_abort_if_not(k > 0);
    a[i] = i + j + k;
  }

  for(int k = 1; k < n; k++) {
    __VERIFIER_assert(a[k] >= (k + 2));
  }
  return 0;
}  
