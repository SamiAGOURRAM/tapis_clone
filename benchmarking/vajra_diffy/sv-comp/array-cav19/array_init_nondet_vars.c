extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    __VERIFIER_error();
  }
}

extern int __VERIFIER_nondet_int();

int n;

int main() {
  n = __VERIFIER_nondet_int();
  int a[n];

  int b[1];

  b[0] = 0;
  int j = __VERIFIER_nondet_int();
  if(j > 0) {
    for(int i = 1; i < n; i++) {
      int k = __VERIFIER_nondet_int();
      if(k > 0) {
        a[i] = i + j + k;
      } else {
        b[0] = 1;
      }
    }

    if(b[0] == 0) {
      for(int k = 1; k < n; k++) {
        __VERIFIER_assert(a[k] >= (k + 2));
      }
    }
  }
  return 0;
}  
