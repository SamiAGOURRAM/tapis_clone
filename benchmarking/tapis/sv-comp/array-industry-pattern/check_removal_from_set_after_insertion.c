int insert(int set[], int size, int value) {
  set[size] = value;
  return size + 1;
}

bool elem_exists(int set[], int size, int value) {
  for(int i = 0; i < size; i++) {
    if(set[i] == value) return true;
  }
  return false;
}

int main() {
  int SIZE;
  assume(SIZE > 0);
  int n = 0;
  int set[SIZE];       // set for storing values
  int values[SIZE];    // array of values to be inserted in the array

  int i = 0;
  for(i = 0; i < SIZE; i++) {
    if(!elem_exists(set, n, values[i])) {
      // parametes are passed by reference
      n = insert(set, n, values[i]);
    }
  }

  int pos;
  int element;           // element to be removed
  bool found = false;
  for(i = 0; i < SIZE && !found; i++) {
    if(set[i] == element) {
      found = true;
      pos = i;
    }
  }
  if(found) {
    for(i = pos; i < SIZE - 1; i++) {
      set[i] = set[i + 1];
    }
  }

  if(found) {
    for(int k = 0; k < SIZE - 1; k++) {
      assert(set[k] != element);
    }
  }
}
