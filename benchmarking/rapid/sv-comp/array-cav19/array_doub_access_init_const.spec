func main()
{
  Int[] a;
  const Int blength;
  Int i = 0;
  while(i <= blength)
  {
    a[2 * i] = 0;
    a[2 * i + 1] = 0;
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (<= 0 blength)
        (<= 0 k)
        (<= k (* 2 blength))
      )
      (>= (a main_end k) 0)
    )
  )
)
