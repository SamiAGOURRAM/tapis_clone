func main()
{
  const Int cellcount;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    if(7 >= 2) {
      volArray[i * 3 - 3] = 7;
    } else {
      volArray[i * 3 - 3] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
    i = i + 1;
  }

  i = 1;
  while(i <= cellcount)
  {
    if(3 >= 2) {
      volArray[i * 3 - 2] = 3;
    } else {
      volArray[i * 3 - 2] = 0;
    }
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
    volArray[i * 3 - 1] = volArray[i * 3 - 1];
    i = i + 1;
  }

  i = 1;
  while(i <= cellcount)
  {
    if(1 >= 2) {
      volArray[i * 3 - 1] = 1;
    } else {
      volArray[i * 3 - 1] = 0;
    }
    volArray[i * 3 - 2] = volArray[i * 3 - 2];
    volArray[i * 3 - 3] = volArray[i * 3 - 3];
    i = i + 1;
  }
}

(conjecture
  (forall ((k Int))
    (=>
      (and
        (> (* 3 cellcount) 1)
        (<= 0 k)
        (< k (* 3 cellcount))
      )
      (or
        (>= (volArray main_end k) 2)
        (= (volArray main_end k) 0)
      )
    )
  )
)
