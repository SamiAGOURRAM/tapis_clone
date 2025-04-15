func main()
{
    Int[] a;
	const Int blength;
	const Int begin;
	const Int end;

    Int pivot = a[end];
    Int i = begin - 1;

    Int j = begin;
    Int tmp = 0;
    while(j <= end - 1) {
        if(a[j] <= pivot) {
          i = i + 1;
          tmp = a[j];
          a[j] = a[i];
          a[i] = tmp;
        } else {
          skip;
        }
    }
  i = i + 1;
  Int tmp1 = a[i];
  a[i] = a[end];
  a[end] = tmp1;
  Int pi = i;
}

(conjecture
    (=>
        (and
            (<= 0 blength)
				(<= 0 begin)
				(<= begin end)
				(<= end blength)
		)
		(and
		   (<= begin (pi main_end))
		   (<= (pi main_end) end)
		   (forall ((l Int))
		(=>
			(and
				(<= begin l)
				(< l (pi main_end))
			)
			(<= (a main_end l) (a main_end (pi main_end)))
		)
	)
	(forall ((l Int))
		(=>
			(and
				(<= (pi main_end) l)
				(< l end)
			)
			(>= (a main_end l) (a main_end (pi main_end)))
		)
	)
		  )
    )

)
