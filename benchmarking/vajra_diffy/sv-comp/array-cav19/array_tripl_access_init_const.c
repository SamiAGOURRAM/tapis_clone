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
  int a[3 * N + 1];

  int i;
  for(i = 0; i <= N; i++) {
    a[3 * i] = 0;
    a[3 * i + 1] = 0;
    a[3 * i + 2] = 0;
  }

  for(int k = 0; k <= 3 * N; k++) {
    __VERIFIER_assert(a[k] >= 0);
  }
  return 0;
}

