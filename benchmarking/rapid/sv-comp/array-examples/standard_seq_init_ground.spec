func main()
{
  const Int blength;
  Int[] a;
  Int i = 1;
  a[0] = 7;

  while(i < blength)
  {
    a[i] = a[i - 1] + 1;
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (< 0 x)
        (< x blength)
      )
      (>= (a main_end x) (a main_end (- x 1)))
    )
  )
)
