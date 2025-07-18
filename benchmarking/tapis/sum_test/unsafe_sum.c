// sum_unsafe_final.c

void assume_exp(const char *);
void assert_exp(const char *);

int main() {
  int a[10];
  int x;

  // Assume 'x' holds the sum of the first 4 elements.
  // x = sum(a, 0, 4)
  assume_exp("(= x (sum a 0 4))");

  // Update x with the 5th element.
  // x's new value is sum(a, 0, 4) + a[4]
  x = x + a[4];

  // Assert an INCORRECT state.
  // This asserts that (sum(a, 0, 4) + a[4]) == sum(a, 0, 4),
  // which is only true if a[4] is 0. Since this is not always true,
  // the program is unsafe.
  assert_exp("(= x (sum a 0 4))");

  return 0;
}