func main()
{
	const Int[] a;
	const Int[] b;
	Int[] c;
	const Int length;

	Int i = 0;
	while(i < length)
	{
		c[i] = a[i] - b[i];
		i = i + 1;
	}
}

(conjecture
	(forall ((j Int))
		(=>
			(and
				(<= 0 j)
				(< j length)
				(<= 0 length)
			)
			(= (c main_end j) (- (a j) (b j)) )
		)
	)
)
