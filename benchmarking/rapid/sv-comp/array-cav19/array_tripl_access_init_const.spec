func main()
{
  const Int blength;
  Int[] a;

  Int i = 0;
  while(i <= blength)
  {
    a[3 * i] = 0;
    a[3 * i + 1] = 0;
    a[3 * i + 2] = 0;
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (>= blength 0)
        (<= 0 k)
        (<= k (* 3 blength))
      )
      (>= (a main_end k) 0)
    )
  )
)
