func main()
{
  const Int cellcount;
  const Int minval;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    if(2 >= minval) {
      volArray[i * 5 - 5] = 2;
    } else {
      volArray[i * 5 - 5] = 0;
    }

    if(5 >= minval) {
      volArray[i * 5 - 4] = 5;
    } else {
      volArray[i * 5 - 4] = 0;
    }

    if(7 >= minval) {
      volArray[i * 5 - 3] = 7;
    } else {
      volArray[i * 5 - 3] = 0;
    }

    if(3 >= minval) {
      volArray[i * 5 - 2] = 3;
    } else {
      volArray[i * 5 - 2] = 0;
    }

    if(1 >= minval) {
      volArray[i * 5 - 1] = 1;
    } else {
      volArray[i * 5 - 1] = 0;
    }
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> (* 5 cellcount) 1)
        (<= 0 k)
        (< k (* 5 cellcount))
      )
      (or
        (>= (volArray main_end k) minval)
        (= (volArray main_end k) 0)
      )
    )
  )
)
