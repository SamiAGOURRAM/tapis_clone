extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "partial_lesser_bound-1.c", 3, "reach_error"); }

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
  int SIZE = __VERIFIER_nondet_int();
  assume_abort_if_not(SIZE > 0);
  int a[SIZE];
  for(int i = 0; i < SIZE; i++) {
    a[i] = 0;
  }

  for(int j = 0; j < SIZE / 2; j++) {
    a[j] = 10;
  }


  for(int k = 0; k < SIZE / 2; k++) {
    __VERIFIER_assert(a[k] == 10);
  }

  return 0;
}	


