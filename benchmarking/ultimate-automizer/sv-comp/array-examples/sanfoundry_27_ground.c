extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "sanfoundry_27_ground.c", 3, "reach_error"); }

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
 * C Program to Find the Largest Number in an Array
 */

int main() {
  int SIZE = __VERIFIER_nondet_int();
  int array[SIZE];
  int i;

  for(i = 0; i < SIZE; i++) {
    array[i] = __VERIFIER_nondet_int();
  }

  int largest = array[0];
  for(i = 1; i < SIZE; i++) {
    if(largest < array[i])
      largest = array[i];
  }

  int x;
  for(x = 0; x < SIZE; x++) {
    __VERIFIER_assert(largest >= array[x]);
  }

  return 0;
}
