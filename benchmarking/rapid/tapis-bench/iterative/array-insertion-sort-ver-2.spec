func main()
{
	Int[] b;
	const Int blength;

  Int i = 1;
  Int j = 1;
  Int tmp = 0;
  Int x = 0;
  while(i < blength) {
    x = b[i];
    j = i - 1;
    while(j >= 0 && b[j] > x) {
      b[j + 1] = b[j];
      j = j - 1;
    }
    b[j + 1] = x;
    i = i + 1;
  }
}

(conjecture
	(forall ((k Int)(l Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 k)
				(<= k l)
				(< l blength)
			)
			(<= (b main_end k) (b main_end l))
		)
	)
)
