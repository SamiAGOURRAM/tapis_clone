func main()
{
	const Int[] b;
	const Int blength;
	Int min = b[0];

	Int i = 0;
	while(i < blength)
	{
	    if(min > b[i])
	    {
	        min = b[i];
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
			(>= (b j) (min main_end))
		)
	)
)
