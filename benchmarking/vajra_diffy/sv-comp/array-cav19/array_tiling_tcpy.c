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
  int a[2 * S];
  int acopy[2 * S];

  for(int i = 0; i < S; i++) {
    acopy[2 * S - (i + 1)] = a[2 * S - (i + 1)];
    acopy[i] = a[i];
  }

  for(int k = 0; k < 2 * S; k++) {
    __VERIFIER_assert(acopy[k] == a[k]);
  }
  return 0;
}

