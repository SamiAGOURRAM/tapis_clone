extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_assert_loop_dep.c", 3, "reach_error"); }

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
    a[i] = 10;
  }

  int z = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= z && z < SIZE);

  for(int j = 0; j < SIZE; j++) {
    __VERIFIER_assert(a[j] == 10);
    if(j + 1 != z) {
      a[j + 1] = 20;
    }
  }

  return 0;
}

