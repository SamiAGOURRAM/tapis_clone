int main() {
  int SIZE;
  assume(SIZE > 0);
  int password[SIZE];
  int guess[SIZE];

  int i;
  bool result = true;

  for(i = 0; i < SIZE; i++) {
    if(password[i] != guess[i]) {
      result = false;
    }
  }

  if(result) {
    for(int x = 0; x < SIZE; x++) {
      assert(password[x] == guess[x]);
    }
  }
  return 0;
}
