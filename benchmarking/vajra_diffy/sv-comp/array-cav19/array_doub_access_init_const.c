extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern int __VERIFIER_nondet_int();

int N;

int main() {
  N = __VERIFIER_nondet_int();
  int a[2 * N + 2];

  for(int i = 0; i <= N; i++) {
    a[2 * i] = 0;
    a[2 * i + 1] = 0;
  }

  for(int k = 0; k <= 2 * N; k++) {
    __VERIFIER_assert(a[k] >= 0);
  }
  return 0;
}
