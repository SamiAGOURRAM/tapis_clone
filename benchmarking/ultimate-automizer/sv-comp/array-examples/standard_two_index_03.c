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

int main() {
  int size = __VERIFIER_nondet_int();
  int a[size];
  int b[size];
  int i = 0;
  int j = 0;
  while(i < size) {
    b[i] = __VERIFIER_nondet_int();
    i = i + 1;
  }

  i = 1;
  while(i < size) {
    a[j] = b[i];
    i = i + 3;
    j = j + 1;
  }

  i = 1;
  j = 0;
  while(i < size) {
    __VERIFIER_assert(a[j] == b[3 * j + 1]);
    i = i + 3;
    j = j + 1;
  }
  return 0;
}
