func main()
{
	const Int[] b;
	const Int blength;
	Int argmax = blength  - 1;

	Int i = blength;

	while(i > 0)
	{
	    if(b[argmax] < b[i - 1])
	    {
	        argmax = i - 1;
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
			(<= (b j) (b (argmax main_end)))
		)
	)
)
