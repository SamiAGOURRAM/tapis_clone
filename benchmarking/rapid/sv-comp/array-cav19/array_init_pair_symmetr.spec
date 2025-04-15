func main()
{
  Int[] a;
  Int[] b;
  Int[] c;
  const Int blength;

  Int i = 0;
  while(i < blength)
  {
    const Int x;
    a[i] = x;
    b[i] = 0 - x;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    c[i] = a[i] + b[i];
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> blength 0)
        (<= 1 k)
        (< k blength)
      )
      (= (c main_end k) 0)
    )
  )
)
