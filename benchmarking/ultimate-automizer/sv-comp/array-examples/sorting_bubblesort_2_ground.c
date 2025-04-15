extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "sorting_bubblesort_2_ground.c", 3, "reach_error"); }

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
  int N = __VERIFIER_nondet_int();
  int a[N];

  for(int j = 0; j < N; j++) {
    a[j] = __VERIFIER_nondet_int();
  }
  int swapped = 1;
  while(swapped) {
    swapped = 0;
    int i = 1;
    while(i < N) {
      if(a[i] > a[i - 1]) {
        int t = a[i];
        a[i] = a[i - 1];
        a[i - 1] = t;
        swapped = 1;
      }
      i = i + 1;
    }
  }

  int x;
  int y;
  for(x = 0; x < N; x++) {
    for(y = x + 1; y < N; y++) {
      __VERIFIER_assert(a[x] <= a[y]);
    }
  }
  return 0;
}
