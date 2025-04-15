func main()
{
	const Int[] b;
	const Int blength;
	Int max = b[0];

	Int i = 0;
	Int k = blength;
	while(i < blength && k > 0 && i <= k)
	{
	    if(max < b[i])
	    {
	        max = b[i];
	    }
	    else
	    {
	        skip;
	    }
	    if(max < b[k - 1])
	    {
	        max = b[k - 1];
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
			)
			(<= (b j) (max main_end))
		)
	)
)
