func main()
{
  const Int blength;
  const Int[] a1;
  Int[] a2;
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
}

(conjecture
  (forall ((l Int))
    (=>
      (and
        (<= 0 z) (< z blength)
        (> blength 0)
        (< l blength)
        (not (= l z))
      )
      (= (a1 l) (a2 main_end l))
    )
  )
)
