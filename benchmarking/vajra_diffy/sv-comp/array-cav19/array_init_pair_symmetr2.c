extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    __VERIFIER_error();
  }
}

extern int __VERIFIER_nondet_int();

int N;

int main() {
  N = __VERIFIER_nondet_int();
  int a[N];
  int b[N];

  int br[1];
  br[0] = 0;

  int i;
  for(i = 0; i < N; i++) {
    int x = __VERIFIER_nondet_int();
    int y = __VERIFIER_nondet_int();
    if(x > y) {
      a[i] = x;
      b[i] = y;
    } else {
      br[0] = 1;
    }
  }

  int c[N];
  for(i = 0; i < N; i++) {
    c[i] = a[i] - b[i];
  }

  if(br[0] == 0) {
    for(int k = 1; k < N; k++) {
      __VERIFIER_assert(c[k] > 0);
    }
  }
  return 0;
}
