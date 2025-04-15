func main()
{
  Int[] a;
  const Int blength;
  const Int j;

  Int i = 1;
  Int kpos = 0;
  while(i < blength)
  {
    const Int m;
    if(m > 0) {
      a[i] = i + j + m;
    } else {
      kpos = 1;
    }
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> blength 0)
        (> j 0)
        (<= 1 k)
        (< k blength)
        (= (kpos main_end) 0)
      )
      (>= (a main_end k) (+ k 2))
    )
  )
)
