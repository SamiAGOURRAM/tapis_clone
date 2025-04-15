func main()
{
    const Int[] a;
	const Int[] b;
	const Int blength;

	Int k = blength;
    Int equal = 1;
	while(k > 0)
	{
	    if(a[k - 1] != b[k - 1])
	    {
	        equal = 0;
	    }
	    else
	    {
	        skip;
	    }
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
				(= (equal main_end) 1)
			)
			(= (b j) (a j))
		)
	)
)
