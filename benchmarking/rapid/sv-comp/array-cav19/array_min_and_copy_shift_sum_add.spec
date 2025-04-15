func main()
{
  const Int blength;
  Int k = 0;
  Int[] a;
  Int[] b;

  Int j;
  Int i = 0;
  while(i < blength)
  {
    if(j > a[i]) {
      j = a[i];
      i = i + 1;
    } else {
      i = i + 1;
    }
  }

  i = 0;
  while(i < blength)
  {
    b[i] = a[i] - j;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    k = k + b[i] + i;
    i = i + 1;
  }
}

(conjecture
  (>= (k main_end) 0)
)
