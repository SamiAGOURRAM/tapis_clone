extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "sanfoundry_24-1.c", 3, "reach_error"); }

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
 * Adapted from http://www.sanfoundry.com/c-programming-examples-arrays/
 * C Program to Print the Number of Odd & Even Numbers in an Array
 */

int main() {
  int SIZE = __VERIFIER_nondet_int();
  int array[SIZE];
  int i;
  int num = __VERIFIER_nondet_int();

  for(i = 0; i < num; i++) {
    array[i] = __VERIFIER_nondet_int();
  }

  //printf("Even numbers in the array are - ");
  for(i = 0; i < num; i++) {
    if(array[i] % 2 == 0) {
      __VERIFIER_assert((i % 2) == 0);
    }
  }
  //printf("\n Odd numbers in the array are -");
  for(i = 0; i < num; i++) {
    if(array[i] % 2 != 0) {
      __VERIFIER_assert((i % 2) != 0);
    }
  }
  return 0;
}
