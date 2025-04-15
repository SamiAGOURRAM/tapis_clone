func main()
{
  const Int cellcount;
  const Int minval;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    if(5 >= minval) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }

    if(7 >= minval) {
      volArray[i * 4 - 3] = 7;
    } else {
      volArray[i * 4 - 3] = 0;
    }

    if(3 >= minval) {
      volArray[i * 4 - 2] = 3;
    } else {
      volArray[i * 4 - 2] = 0;
    }

    if(1 >= minval) {
      volArray[i * 4 - 1] = 1;
    } else {
      volArray[i * 4 - 1] = 0;
    }
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> (* 4 cellcount) 1)
        (<= 0 k)
        (< k (* 4 cellcount))
      )
      (or
        (>= (volArray main_end k) minval)
        (= (volArray main_end k) 0)
      )
    )
  )
)
