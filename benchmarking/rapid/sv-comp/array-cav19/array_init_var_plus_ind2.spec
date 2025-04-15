func main()
{
  const Int blength;
  Int j = 0;
  Int k = 0;
  Int[] a;

  Int i = 0;
  Int break_flag = 0;
  while(i < blength)
  {
    const Int x;
    if(x == 0) {
      break_flag = 1;
    } else {
      a[i] = j;
      j = j + i;
      k = k - i;
      i = i + 1;
    }
  }
}

(conjecture
  (forall ((l Int))
    (=>
      (and
        (> blength 0)
        (<= 1 l)
        (< l (i main_end))
        (= (break_flag main_end) 0)
      )
      (>= (a main_end l) (k main_end))
    )
  )
)
