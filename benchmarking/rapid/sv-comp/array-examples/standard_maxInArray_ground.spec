func main()
{
  const Int blength;
  const Int[] a;
  Int max = 0;

  Int i = 0;
  while(i < blength)
  {
    if(a[i] > max) {
      max = a[i];
      i = i + 1;
    } else {
      i = i + 1;
    }
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
      (<= (a x) (max main_end))
    )
  )
)
