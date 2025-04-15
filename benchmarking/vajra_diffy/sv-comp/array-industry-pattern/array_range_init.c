extern void __VERIFIER_error() __attribute__ ((__noreturn__));

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    __VERIFIER_error();
  }
}

extern int __VERIFIER_nondet_int();

int SIZE;

int main() {
  SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  int uv = __VERIFIER_nondet_int();
  if(0 <= uv && uv < SIZE) {
    for(int i = 0; i < SIZE; i++) {
      if(i >= 0 && i <= uv) {
        a[i] = 1;
      } else {
        a[i] = 0;
      }
    }

    for(int k = 0; k < SIZE; k++) {
      __VERIFIER_assert(a[k] == 1);
    }
  }

  return 0;
}
