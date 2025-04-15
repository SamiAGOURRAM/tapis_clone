extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "array_mul_init.c", 3, "reach_error"); }

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
  int b[SIZE];
  int c[SIZE];

  //init and update
  for(int i = 0; i < SIZE; i++) {
    int q = __VERIFIER_nondet_int();
    a[i] = 0;
    if(q != 0) {
      a[i] = 1;
      b[i] = i % 2;
    }
    if(a[i] != 0) {
      if(b[i] == 0) {
        c[i] = 0;
      } else {
        c[i] = 1;
      }
    }
  }

  int iv = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= iv && iv < SIZE);
  a[iv] = 1;

  for(int j = 0; j < SIZE; j++) {
    if(j == iv) {
      __VERIFIER_assert(a[j] != 1);
    }
  }
  return 0;
}

