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

/* Invited talk at ETAPS 2014 */

int main() {
  int SIZE = __VERIFIER_nondet_int();
  int password[SIZE];
  int guess[SIZE];

  int i;
  int result = 1;

  for(i = 0; i < SIZE; i++) {
    password[i] = __VERIFIER_nondet_int();
    guess[i] = __VERIFIER_nondet_int();
  }

  for(i = 0; i < SIZE; i++) {
    if(password[i] != guess[i]) {
      result = 0;
    }
  }

  if(result) {
    int x;
    for(x = 0; x < SIZE; x++) {
      __VERIFIER_assert(password[x] == guess[x]);
    }
  }
  return 0;
}
