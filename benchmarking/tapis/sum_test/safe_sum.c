// sum_safe_final.c

void assume_exp(const char *);
void assert_exp(const char *);

int main() {
  int a[10];
  int x;

  // Assume 'x' holds the sum of the first 4 elements.
  // x = sum(a, 0, 4)
  assume_exp("(= x (sum a 0 4))");

  // Update x with the 5th element.
  // After this, x's value is sum(a, 0, 4) + a[4]
  x = x + a[4];


  assert_exp("(= x (sum a 0 5))");

  return 0;
}