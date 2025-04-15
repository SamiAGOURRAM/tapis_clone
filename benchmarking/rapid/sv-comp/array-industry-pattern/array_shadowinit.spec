func main()
{
  const Int blength;

    Int i = 0;
    Int k = 0;
    Int[] a;

    while(i < blength)
    {
      a[k] = k;
      i = i + 1;
      k = k + 1;
    }
}

(conjecture
  (forall ((l Int))
    (=>
      (and
        (> blength 0)
        (<= 0 l)
        (< l blength)
      )
      (= (a main_end l) l)
    )
  )
)
