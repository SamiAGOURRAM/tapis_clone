func main()
{
  const Int blength;
  const Int[] a;
  Int min = 0;

  Int i = 0;
  while(i < blength)
  {
    if(a[i] < min) {
      min = a[i];
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
      (>= (a x) (min main_end))
    )
  )
)
