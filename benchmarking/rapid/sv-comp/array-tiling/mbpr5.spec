func main()
{
  const Int cellcount;

  Int[] volArray;

  Int i = 1;
  while(i <= cellcount)
  {
    if(8 >= 2) {
      volArray[i * 5 - 5] = 8;
    } else {
      volArray[i * 5 - 5] = 0;
    }
    volArray[i * 5 - 4] = volArray[i * 5 - 4];
    volArray[i * 5 - 3] = volArray[i * 5 - 3];
    volArray[i * 5 - 2] = volArray[i * 5 - 2];
    volArray[i * 5 - 1] = volArray[i * 5 - 1];
    i = i + 1;
  }

  Int j = 1;
  while(j <= cellcount)
  {
    if(5 >= 2) {
      volArray[j * 5 - 4] = 5;
    } else {
      volArray[j * 5 - 4] = 0;
    }
    volArray[j * 5 - 5] = volArray[j * 5 - 5];
    volArray[j * 5 - 3] = volArray[j * 5 - 3];
    volArray[j * 5 - 2] = volArray[j * 5 - 2];
    volArray[j * 5 - 1] = volArray[j * 5 - 1];
    j = j + 1;
  }

  Int k = 1;
  while(k <= cellcount)
  {
    if(7 >= 2) {
      volArray[k * 5 - 3] = 7;
    } else {
      volArray[k * 5 - 3] = 0;
    }
    volArray[k * 5 - 5] = volArray[k * 5 - 5];
    volArray[k * 5 - 4] = volArray[k * 5 - 4];
    volArray[k * 5 - 2] = volArray[k * 5 - 2];
    volArray[k * 5 - 1] = volArray[k * 5 - 1];
    k = k + 1;
  }

  Int l = 1;
  while(l <= cellcount)
  {
    if(3 >= 2) {
      volArray[l * 5 - 2] = 3;
    } else {
      volArray[l * 5 - 2] = 0;
    }
    volArray[l * 5 - 5] = volArray[l * 5 - 5];
    volArray[l * 5 - 4] = volArray[l * 5 - 4];
    volArray[l * 5 - 3] = volArray[l * 5 - 3];
    volArray[l * 5 - 1] = volArray[l * 5 - 1];
    l = l + 1;
  }

  Int m = 1;
  while(m <= cellcount)
  {
    if(1 >= 2) {
      volArray[m * 5 - 1] = 1;
    } else {
      volArray[m * 5 - 1] = 0;
    }
    volArray[m * 5 - 5] = volArray[m * 5 - 5];
    volArray[m * 5 - 4] = volArray[m * 5 - 4];
    volArray[m * 5 - 3] = volArray[m * 5 - 3];
    volArray[m * 5 - 2] = volArray[m * 5 - 2];
    m = m + 1;
  }
}

(conjecture
  (forall ((n Int))
    (=>
      (and
        (> (* 5 cellcount) 1)
        (<= 0 n)
        (< n (* 5 cellcount))
      )
      (or
        (>= (volArray main_end n) 2)
        (= (volArray main_end n) 0)
      )
    )
  )
)
