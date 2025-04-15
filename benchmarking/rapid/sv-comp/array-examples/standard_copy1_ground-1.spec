func main()
{
  const Int[] a1;
  Int[] a2;

  const Int blength;

  Int i = 0;
  while(i < blength)
  {
    a2[i] = a1[i];
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (<= 0 blength)
        (<= 0 x)
        (< x blength)
      )
      (= (a1 x) (a2 main_end x))
    )
  )
)
