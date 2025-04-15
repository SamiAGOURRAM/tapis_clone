func main()
{
	Int[] a;
	const Int blength;

  Int i = 0;
  while(i < blength - 1) {
    Int jmin = i;
    Int j = i + 1;
    while(j < blength) {
      if(a[j] < a[jmin]) {
        jmin = j;
      } else {
        skip;
      }
      j = j + 1;
    }
    if(jmin != i) {
      Int tmp = a[jmin];
      a[jmin] = a[i];
      a[i] = tmp;
    } else {
        skip;
    }
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
			(<= (a main_end k) (a main_end l))
		)
	)
)
