func main()
{
  const Int blength;
  Int[] a;
  Int e;
  Int i = 0;

  while(i < blength && a[i] != e)
  {
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x (i main_end))
      )
      (not (= (a main_end x) (e main_end)))
    )
  )
)
