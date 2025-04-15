func main()
{
	const Int[] b;
	const Int blength;
	Int[] a;

	Int i = blength;

	while(i > 0)
	{
		a[i - 1] = b[i - 1];
		i = i - 1;
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
			(= (a main_end j) (b j))
		)
	)
)
