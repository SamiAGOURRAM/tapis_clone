extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    __VERIFIER_error();
  }
}

extern int __VERIFIER_nondet_int();

int S;

int main() {
  S = __VERIFIER_nondet_int();
  int a[S];

  int i;
  for(i = 0; i < S; i++) {
    a[i] = ((i - 1) * (i + 1));
  }

  for(i = 0; i < S; i++) {
    a[i] = a[i] - (i * i);
  }

  for(int k = 0; k < S; k++) {
    __VERIFIER_assert(a[k] == -1);
  }
  return 0;
}

