func main()
{
	const Int[] b;
	const Int blength;
	Int max = b[0];

	Int i = 0;
	while(i < blength)
	{
	    if(max < b[i])
	    {
	        max = b[i];
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
			(<= (b j) (max main_end))
		)
	)
)
