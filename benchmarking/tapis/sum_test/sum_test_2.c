//
// Copyright (c) 2024 Wael-Amine Boutglay
//

// Forward declarations for the verification tool's special functions.
// 'assume' is often a built-in intrinsic for the verifier front-end.
void assume(int);
void assert_exp(const char *);

int main() {

int N;
assume(N > 0);
int a[N];
long s = 0;

int i;
for (i = 0; i < N; i++) {
  s = s + a[i];
}

for (i = 0; i < N; i++) {
  s = s - a[i];
}
assert(s == 0);
  return 0;
}