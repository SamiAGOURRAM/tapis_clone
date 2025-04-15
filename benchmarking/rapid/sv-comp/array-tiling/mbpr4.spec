func main()
{
  const Int cellcount;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    if(5 >= 2) {
      volArray[i * 4 - 4] = 5;
    } else {
      volArray[i * 4 - 4] = 0;
    }
    volArray[i * 4 - 3] = volArray[i * 4 - 3];
    volArray[i * 4 - 2] = volArray[i * 4 - 2];
    volArray[i * 4 - 1] = volArray[i * 4 - 1];
    i = i + 1;
  }

  Int j = 1;
  while(j <= cellcount)
  {
    if(7 >= 2) {
      volArray[j * 4 - 3] = 7;
    } else {
      volArray[j * 4 - 3] = 0;
    }
    volArray[j * 4 - 4] = volArray[j * 4 - 4];
    volArray[j * 4 - 2] = volArray[j * 4 - 2];
    volArray[j * 4 - 1] = volArray[j * 4 - 1];
    j = j + 1;
  }

  Int k = 1;
  while(k <= cellcount)
  {
    if(3 >= 2) {
      volArray[k * 4 - 2] = 3;
    } else {
      volArray[k * 4 - 2] = 0;
    }
    volArray[k * 4 - 4] = volArray[k * 4 - 4];
    volArray[k * 4 - 3] = volArray[k * 4 - 3];
    volArray[k * 4 - 1] = volArray[k * 4 - 1];
    k = k + 1;
  }

  Int l = 1;
  while(l <= cellcount)
  {
    if(1 >= 2) {
      volArray[l * 4 - 1] = 1;
    } else {
      volArray[l * 4 - 1] = 0;
    }
    volArray[l * 4 - 4] = volArray[l * 4 - 4];
    volArray[l * 4 - 3] = volArray[l * 4 - 3];
    volArray[l * 4 - 2] = volArray[l * 4 - 2];
    l = l + 1;
  }
}

(conjecture
  (forall ((m Int))
    (=>
      (and
        (> (* 4 cellcount) 1)
        (<= 0 m)
        (< m (* 4 cellcount))
      )
      (or
        (>= (volArray main_end m) 2)
        (= (volArray main_end m) 0)
      )
    )
  )
)
