func main()
{
  const Int blength;
  const Int[] a;
  const Int[] b;
  Int[] c;

  Int i = 0;
  Int rv = 1;
  while(i < blength)
  {
    if(a[i] != b[i]) {
      rv = 0;
      c[i] = a[i];
      i = i + 1;
    } else {
      c[i] = a[i];
      i = i + 1;
    }
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> blength 0)
        (<= 0 k)
        (< k blength)
        (= (rv main_end) 1)
      )
      (= (a k) (b k))
    )
  )
)

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x blength)
      )
      (= (a x) (c main_end x))
    )
  )
)
