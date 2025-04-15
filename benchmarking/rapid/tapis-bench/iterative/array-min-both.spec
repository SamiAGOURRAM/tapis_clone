func main()
{
	const Int[] b;
	const Int blength;
	Int min = b[0];

	Int i = 0;
	Int k = blength;
	while(i < blength && k > 0 && i <= k)
	{
	    if(min > b[i])
	    {
	        min = b[i];
	    }
	    else
	    {
	        skip;
	    }
	    if(min > b[k - 1])
	    {
	        min = b[k - 1];
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
			(>= (b j) (min main_end))
		)
	)
)
