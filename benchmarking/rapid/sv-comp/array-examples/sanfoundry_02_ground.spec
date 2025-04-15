func main()
{
  const Int blength;
  Int[] array;
  Int largest1;
  Int largest2;
  Int temp;

  largest1 = array[0];
  largest2 = array[1];

  if(largest1 < largest2) {
    temp = largest1;
    largest1 = largest2;
    largest2 = temp;
  } else {
    largest1 = array[0];
    largest2 = array[1];
  }

  Int i = 2;
  while(i < blength)
  {
    if(array[i] >= largest1) {
      largest2 = largest1;
      largest1 = array[i];
      i = i + 1;
    } else {
      if(array[i] > largest2) {
        largest2 = array[i];
        i = i + 1;
      } else {
        i = i + 1;
      }
    }
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x blength)
      )
      (<= (array main_end x) (largest1 main_end))
    )
  )
)

(conjecture
  (forall ((y Int))
    (=>
      (and
        (> blength 0)
        (<= 0 y)
        (< y blength)
      )
      (or
        (<= (array main_end y) (largest2 main_end))
        (= (array main_end y) (largest1 main_end))
      )
    )
  )
)
