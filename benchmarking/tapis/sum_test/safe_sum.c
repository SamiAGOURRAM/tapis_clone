//
// Copyright (c) 2024 Wael-Amine Boutglay
//

// Forward declarations for the verification tool's special functions.
// 'assume' is often a built-in intrinsic for the verifier front-end.
void assume(int);
void assert_exp(const char *);

int main() {

  //*-- precondition
  unsigned int N;
  // Assume a reasonable, bounded size for the array to make verification tractable.
  assume(N >= 0);
  int array[N];

  //*-- computation
  // A simple C loop to calculate the sum of the array's elements.
  // The verifier's task is to discover a loop invariant for 's' and 'i'.
  // The expected invariant is: i <= N && s == sum(array, 0, i)
  int s = 0;
  unsigned int i = 0;

  assume(s==0);
  assume(i==0);
  while(i < N) {
    s = s + array[i];
    i = i + 1;
  }

  //*-- specification
  // After the loop terminates, the verifier knows that i == N.
  // The assertion uses the background 'sum' theory (provided to the SMT solver)
  // to check if the computed value 's' matches the symbolic sum of the entire array.
  assert_exp("(= s (sum array 0 N))");

  return 0;
}