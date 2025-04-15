func main()
{
	const Int[] b;
	const Int blength;
	Int argmin = 0;

	Int i = 0;
	Int k = blength;

	while(i < blength && k > 0 && i <= k)
	{
	    if(b[argmin] > b[i])
	    {
	        argmin = i;
	    }
	    else
	    {
	        skip;
	    }
	    if(b[argmin] > b[k - 1])
	    {
	        argmin = k - 1;
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
			(>= (b j) (b (argmin main_end)))
		)
	)
)
