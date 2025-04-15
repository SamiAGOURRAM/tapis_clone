func main()
{
	const Int blength;
	Int[] a;

    Int k = blength;
	while(k > 0)
	{
		a[k - 1] = k - 1;
		k = k - 1;
	}
}

(conjecture
	(forall ((j Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 j)
				(< j blength)
			)
			(= (a main_end j) j)
		)
	)
)
