extern void __VERIFIER_error() __attribute__ ((__noreturn__));
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: __VERIFIER_error(); } }
extern int __VERIFIER_nondet_int();

int N;

int main() {
  N = __VERIFIER_nondet_int();
  int a1[N];
  int a2[N];
  int a3[N];

  int i;
  for(i = 0; i < N; i++) {
    a1[i] = __VERIFIER_nondet_int();
    a2[i] = __VERIFIER_nondet_int();
    a3[i] = __VERIFIER_nondet_int();
  }

  int z = __VERIFIER_nondet_int();
  if(0 <= z && z < N) {
    for(i = 0; i < N; i++) {
    if(i != z)
      a2[i] = a1[i];
  }
  for(i = 0; i < N; i++) {
    if(i != z)
      a3[i] = a2[i];
    else
      a3[i] = a1[i];
  }

  for(int x = 0; x < N; x++) {
    __VERIFIER_assert(a1[x] == a3[x]);
  }
  }

  return 0;
}

