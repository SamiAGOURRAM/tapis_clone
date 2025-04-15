func main()
{
  const Int blength;
  Int[] a;

  Int i = 0;
  while(i < blength)
  {
    a[i] = 42;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    a[i] = 43;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    a[i] = 44;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    a[i] = 45;
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x blength)
      )
      (= (a main_end x) 45)
    )
  )
)
