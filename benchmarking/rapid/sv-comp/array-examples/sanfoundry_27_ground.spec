func main()
{
  const Int blength;
  Int[] array;
  Int largest = array[0];

  Int i = 1;
  while(i < blength)
  {
    if(largest < array[i]) {
      largest = array[i];
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
        (<= 0 x)
        (< x blength)
      )
      (>= (largest main_end) (array main_end x))
    )
  )
)
