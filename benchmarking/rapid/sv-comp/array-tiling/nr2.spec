func main()
{
  const Int cellcount;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    Int j = 2;
    while(j >= 1)
    {
      if(j >= 2) {
        volArray[i * 2 - j] = j;
      } else {
        volArray[i * 2 - j] = 0;
      }
      j = j - 1;
    }
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> (* 2 cellcount) 1)
        (<= 0 k)
        (< k (* 2 cellcount))
      )
      (or
        (>= (volArray main_end k) 2)
        (= (volArray main_end k) 0)
      )
    )
  )
)
