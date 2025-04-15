func main()
{
  Int[] a;
  Int[] b;
  Int[] c;
  const Int blength;

  Int i = 0;
  Int xy_pos = 0;
  while(i < blength)
  {
    const Int x;
    const Int y;
    if(x > y) {
      a[i] = x;
      b[i] = y;
    } else {
      xy_pos = 1;
    }
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    c[i] = a[i] - b[i];
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> blength 0)
        (<= 1 k)
        (= (xy_pos main_end) 0)
        (< k blength)
      )
      (> (c main_end k) 0)
    )
  )
)
