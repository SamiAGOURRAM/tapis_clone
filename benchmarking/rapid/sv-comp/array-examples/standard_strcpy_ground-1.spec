func main()
{
  const Int blength;
  const Int[] src;
  Int[] dst;
  Int i = 0;

  while((i < blength) && (src[i] != 0))
  {
    dst[i] = src[i];
    i = i + 1;
  }
}

(conjecture
  (forall ((x Int))
    (=>
      (and
        (> blength 0)
        (<= 0 x)
        (< x (i main_end))
      )
      (= (dst main_end x) (src x))
    )
  )
)
