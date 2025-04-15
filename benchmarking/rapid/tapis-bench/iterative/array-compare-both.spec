func main()
{
    const Int[] a;
	const Int[] b;
	const Int blength;

	Int i = 0;
	Int k = blength;
    Int equal = 1;
	while(i < blength && k > 0 && i <= k)
	{
	    if(a[k - 1] != b[k - 1])
	    {
	        equal = 0;
	    }
	    else
	    {
	        skip;
	    }
	    if(a[i] != b[i])
	    {
	        equal = 0;
	    }
	    else
	    {
	        skip;
	    }
		i = i + 1;
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
