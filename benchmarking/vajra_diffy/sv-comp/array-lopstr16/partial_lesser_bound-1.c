extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern int __VERIFIER_nondet_int();

int SIZE;

int main() {
  SIZE = __VERIFIER_nondet_int();
  int a[SIZE];
  for(int i = 0; i < SIZE; i++) {
    a[i] = 0;
  }

  for(int j = 0; j < SIZE / 2; j++) {
    a[j] = 10;
  }


  for(int k = 0; k < SIZE / 2; k++) {
    __VERIFIER_assert(a[k] == 10);
  }

  return 0;
}	


