func main()
{
  const Int blength;
  Int[] a;
  Int[] b;
  Int i = 0;

  while(i < blength)
  {
    if(a[i] >= 0) {
      b[i] = 1;
    } else {
      b[i] = 0;
    }
    i = i + 1;
  }

  Int f = 1;
  i = 0;
  while(i < blength)
  {
    if(a[i] >= 0 && b[i] == 0) {
      f = 0;
    } else {
      f = f;
    }
    if(a[i] < 0 && b[i] == 1) {
      f = 0;
    } else {
      f = f;
    }
    i = i + 1;
  }
}

(conjecture
  (= (f main_end) 1)
)
