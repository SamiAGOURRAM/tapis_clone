func main()
{
  const Int blength;
  Int[] a;

  Int i = 0;
  while(i < blength)
  {
    a[i] = ((i - 1) * (i + 1));
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    a[i] = a[i] - (i * i);
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> blength 0)
        (<= 0 k)
        (< k blength)
      )
      (= (a main_end k) (- 0 1))
    )
  )
)
