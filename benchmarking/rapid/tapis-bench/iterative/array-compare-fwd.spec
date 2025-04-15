func main()
{
    const Int[] a;
	const Int[] b;
	const Int blength;

	Int i = 0;
    Int equal = 1;
	while(i < blength)
	{
	    if(a[i] != b[i])
	    {
	        equal = 0;
	    }
	    else
	    {
	        skip;
	    }
		i = i + 1;
	}
}

(conjecture
	(forall ((j Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 j)
				(< j blength)
				(= (equal main_end) 1)
			)
			(= (b j) (a j))
		)
	)
)
