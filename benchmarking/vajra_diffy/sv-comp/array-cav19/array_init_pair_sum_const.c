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

  int i;
  for(i = 0; i < N; i++) {
    a[i] = 1;
    b[i] = 2;
  }

  int c[N];
  for(i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
  }

  for(int k = 1; k < N; k++) {
    __VERIFIER_assert(c[k] >= 3);
  }
  return 0;
}


