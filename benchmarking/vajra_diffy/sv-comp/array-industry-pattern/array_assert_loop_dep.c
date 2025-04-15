extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern int __VERIFIER_nondet_int();

int SIZE;

int main() {
  SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  for(int i = 0; i < SIZE; i++) {
    a[i] = 10;
  }

  int z[1];
  z[0] = __VERIFIER_nondet_int();
  if(0 <= z[0] && z[0] < SIZE) {

    for(int j = 0; j < SIZE; j++) {
      __VERIFIER_assert(a[j] == 10);
      if(j + 1 != z[0]) {
        a[j + 1] = 20;
      }
    }
  }

  return 0;
}

