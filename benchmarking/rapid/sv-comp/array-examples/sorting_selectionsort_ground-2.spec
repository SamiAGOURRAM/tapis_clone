func main()
{
  const Int blength;
  Int[] a;

  Int swapped = 1;
  while(swapped == 1)
  {
    swapped = 0;
    Int i = 1;
    while(i < blength)
    {
      if(a[i - 1] > a[i]) {
        Int t = a[i];
        a[i] = a[i - 1];
        a[i - 1] = t;
        swapped = 1;
        i = i + 1;
      } else {
        i = i + 1;
      }
    }
  }
}

(conjecture
  (forall ((x Int) (y Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x blength)
        (< x y)
        (< y blength)
      )
      (<= (a main_end x) (a main_end y))
    )
  )
)
