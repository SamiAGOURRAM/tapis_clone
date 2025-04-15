func main()
{
    Int[] a;
	const Int blength;
	const Int begin;
	const Int end;

    Int k = end;
	while(k >= begin)
	{
		a[k - 1] = 0;
		k = k - 1;
	}
}

(conjecture
	(forall ((j Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 begin)
				(<= begin end)
				(<= end blength)
				(<= begin j)
				(< j end)
			)
			(= (a main_end j) 0)
		)
	)
)
