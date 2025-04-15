func main()
{
  const Int blength;
  Int[] a;
  Int[] b;

  Int i = 0;
  while(i < blength)
  {
    a[i] = i;
    b[i] = i;
    i = i + 1;
  }

  i = 0;
  while(i < blength)
  {
    const Int bo;
    if(bo == 1) {
      const Int k;
      a[i] = k;
      b[i] = k * k;
      i = i + 1;
    } else {
      i = i + 1;
    }
  }
}

(conjecture
  (forall ((l Int))
    (=>
      (and
        (> blength 0)
        (< l blength)
      )
      (or
        (= (a main_end l) (b main_end l))
        (= (b main_end l) (* (a main_end l) (a main_end l)))
      )
    )
  )
)
