func main()
{
  const Int blength;
  const Int[] password;
  const Int[] guess;

  Int i = 0;
  Int result = 1;

  while(i < blength)
  {
    if(password[i] != guess[i]) {
      result = 0;
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
        (= (result main_end) 1)
      )
      (= (password x) (guess x))
    )
  )
)
