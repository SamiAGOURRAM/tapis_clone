extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern int __VERIFIER_nondet_int();

int SIZE;

int main() {
  SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  int b[SIZE];

  for(int i = 0; i < SIZE; i = i + 2) {
    a[i] = __VERIFIER_nondet_int();
    if(a[i] == 10) {
      b[i] = 20;
    }
  }

  for(int j = 0; j < SIZE; j = j + 2) {
    if(a[j] == 10) {
      __VERIFIER_assert(b[j] == 20);
    }
  }
}

