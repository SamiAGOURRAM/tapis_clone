func main()
{
	const Int[] b;
	const Int blength;
	Int argmin = 0;

	Int i = 0;

	while(i < blength)
	{
	    if(b[argmin] >= b[i])
	    {
	        argmin = i;
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
			)
			(>= (b j) (b (argmin main_end)))
		)
	)
)
