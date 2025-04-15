func main()
{
	const Int[] b;
	const Int blength;
	Int min = b[0];

	Int k = blength;
	while(k > 0)
	{
	    if(min > b[k - 1])
	    {
	        min = b[k - 1];
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
			)
			(>= (b j) (min main_end))
		)
	)
)
