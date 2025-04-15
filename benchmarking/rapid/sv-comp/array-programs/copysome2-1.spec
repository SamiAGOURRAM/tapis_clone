func main()
{
  const Int blength;
  const Int[] a1;
  Int[] a2;
  Int[] a3;
  const Int z;

  Int i = 0;
  while(i < blength)
  {
    if(i != z)
    {
      a2[i] = a1[i];
      i = i + 1;
    } else {
      i = i + 1;
    }
  }

  i = 0;
  while(i < blength)
  {
    if(i != z)
    {
      a3[i] = a2[i];
    } else {
      a3[i] = a1[i];
    }
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (<= 0 z) (< z blength)
        (> blength 0)
        (< x blength)
      )
      (= (a1 x) (a3 main_end x))
    )
  )
)
