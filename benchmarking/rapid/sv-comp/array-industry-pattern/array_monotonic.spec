func main()
{
  const Int blength;
  const Int[] a;
  Int[] b;

  Int i = 0;
  while(i < blength)
  {
    if(a[i] == 10) {
      b[i] = 20;
      i = i + 2;
    } else {
      i = i + 2;
    }
  }
}

(conjecture
  (forall ((j Int))
    (=>
      (and
        (> blength 0)
        (< j blength)
        (= (mod j 2) 0)
        (= (a j) 10)
      )
      (= (b main_end j) 20)
    )
  )
)
