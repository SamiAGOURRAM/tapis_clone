// sum_unsafe_final.c

void assume_exp(const char *);
void assert_exp(const char *);

int main() {
  int a[10];
  int x;

  assume_exp("(= x (sum a 0 4))");

  x = x + 1;

  assert_exp("(= x (sum a 0 1))");

  return 0;
}