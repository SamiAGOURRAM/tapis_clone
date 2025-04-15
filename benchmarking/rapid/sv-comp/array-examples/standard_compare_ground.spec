func main()
{
  const Int blength;
  const Int[] a;
  const Int[] b;

  Int i = 0;
  Int rv = 1;
  while(i < blength)
  {
    if(a[i] != b[i]) {
      rv = 0;
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
        (= (rv main_end) 1)
      )
      (= (a x) (b x))
    )
  )
)
