int insert(int set[], int size, int value) {
  set[size] = value;
  return size + 1;
}

bool elem_exists(int set[], int size, int value) {
  int i;
  for(i = 0; i < size; i++) {
    if(set[i] == value) return true;
  }
  return false;
}

int main() {
  int SIZE;
  assume(SIZE > 0);
  int n = 0;
  int set[SIZE];

  // this is trivial
  for(int x = 0; x < n; x++) {
    for(int y = x + 1; y < n; y++) {
      assert(set[x] != set[y]);
    }
  }

  // we have an array of values to insert
  int values[SIZE];

  // insert them in the array -- note that nothing ensures that values is not containing duplicates!
  for(int v = 0; v < SIZE; v++) {
    // check if the element exists, if not insert it.
    if(!elem_exists(set, n, values[v])) {
      // parametes are passed by reference
      n = insert(set, n, values[v]);
    }
  }

  // this is not trivial!
  for(int z = 0; z < n; z++) {
    for(int u = z + 1; u < n; u++) {
      assert(set[z] != set[u]);
    }
  }
  return 0;
}

