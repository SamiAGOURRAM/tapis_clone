func main()
{
	const Int[] b;
	const Int blength;
	Int argmin = blength  - 1;

	Int i = blength;

	while(i > 0)
	{
	    if(b[argmin] > b[i - 1])
	    {
	        argmin = i - 1;
	    }
	    else
	    {
	        skip;
	    }
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
			(>= (b j) (b (argmin main_end)))
		)
	)
)
