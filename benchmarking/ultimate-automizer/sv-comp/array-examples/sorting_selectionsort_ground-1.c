extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "sorting_selectionsort_ground-1.c", 3, "reach_error"); }

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
  int i = 0;
  int x;
  int y;

  for(int i = 0; i < 100000; i++) {
    a[i] = __VERIFIER_nondet_int();
  }

  i = 0;
  while(i < N) {
    int k = i + 1;
    int s = i;
    while(k < N) {
      if(a[k] < a[s]) {
        s = k;
      }
      k = k + 1;
    }
    if(s != i) {
      int tmp = a[s];
      a[s] = a[i];
      a[i] = tmp;
    }

    for(x = 0; x < i; x++) {
      for(y = x + 1; y < i; y++) {
        __VERIFIER_assert(a[x] <= a[y]);
      }
    }
    for(x = 0; x < N; x++) {
      __VERIFIER_assert(a[x] >= a[i]);
    }

    i = i + 1;
  }

  for(x = 0; x < N; x++) {
    for(y = x + 1; y < N; y++) {
      __VERIFIER_assert(a[x] <= a[y]);
    }
  }
  return 0;
}
