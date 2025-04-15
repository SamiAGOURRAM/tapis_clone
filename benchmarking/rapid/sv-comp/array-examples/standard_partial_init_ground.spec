func main()
{
  const Int blength;
  Int[] a;
  Int[] b;
  Int[] c;
  Int i;
  Int j = 0;

  i = 0;
  while(i < blength)
  {
    if(a[i] == b[i]) {
      c[j] = i;
      j = j + 1;
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
        (< x (j main_end))
      )
      (<= (c main_end x) (+ x (- (i main_end) (j main_end))))
    )
  )
)

(conjecture
  (forall ((y Int))
    (=>
      (and
        (> blength 0)
        (< y (j main_end))
      )
      (>= (c main_end y) y)
    )
  )
)
