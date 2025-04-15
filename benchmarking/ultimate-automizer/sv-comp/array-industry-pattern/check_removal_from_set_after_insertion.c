extern void abort(void);

extern void __assert_fail(const char *, const char *, unsigned int,
                          const char *) __attribute__ ((__nothrow__, __leaf__)) __attribute__ ((__noreturn__));

void reach_error() { __assert_fail("0", "check_removal_from_set_after_insertion.c", 3, "reach_error"); }

extern void abort(void);

void assume_abort_if_not(int cond) {
  if(!cond) { abort(); }
}

void __VERIFIER_assert(int cond) {
  if(!(cond)) {
    ERROR:
    {
      reach_error();
      abort();
    }
  }
}

extern int __VERIFIER_nondet_int();

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
  int SIZE = __VERIFIER_nondet_int();
  assume_abort_if_not(SIZE > 0);
  int n = 0;
  int set[SIZE];       // set for storing values
  int values[SIZE];    // array of values to be inserted in the array

  int i = 0;
  for(i = 0; i < SIZE; i++) {
    set[i] = __VERIFIER_nondet_int();
    values[i] = __VERIFIER_nondet_int();
  }

  for(i = 0; i < SIZE; i++) {
    if(!elem_exists(set, n, values[i])) {
      // parametes are passed by reference
      n = insert(set, n, values[i]);
    }
  }

  int pos;
  int element = __VERIFIER_nondet_int();;           // element to be removed
  int found = 0;
  for(i = 0; i < SIZE && found == 0; i++) {
    if(set[i] == element) {
      found = 1;
      pos = i;
    }
  }
  if(found == 1) {
    for(i = pos; i < SIZE - 1; i++) {
      set[i] = set[i + 1];
    }
  }

  if(found == 1) {
    for(int k = 0; k < SIZE - 1; k++) {
      __VERIFIER_assert(set[k] != element);
    }
  }
}
