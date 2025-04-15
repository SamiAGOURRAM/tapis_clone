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
  int k = 0;
  int a[N + 1];
  int b[N];

  int j = __VERIFIER_nondet_int();
  int i;
  for(i = 0; i < N; i++) {
    if(j > a[i]) {
      j = a[i];
    }
  }

  for(i = 0; i < N; i++) {
    b[i] = a[i] - j;
  }

  for(i = 0; i < N; i++) {
    k = k + b[i] + i;
  }

  __VERIFIER_assert(k >= 0);
  return 0;
}
