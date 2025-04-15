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

/*
  From: "On Solving Universally Quantified Horn Clauses"
  Bjorner, McMillan, and Rybalchenko
  SAS 2013
*/

int main() {
  int SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  int b[SIZE];
  int c[SIZE];
  int i = 0;

  for(i = 0; i < SIZE; i++) {
    a[i] = __VERIFIER_nondet_int();
    b[i] = __VERIFIER_nondet_int();
  }

  i = 0;
  while(i < SIZE) {
    c[i] = a[i] - b[i];
    i = i + 1;
  }

  int x;
  for(x = 0; x < SIZE; x++) {
    __VERIFIER_assert(c[x] == a[x] - b[x]);
  }
  return 0;
}

