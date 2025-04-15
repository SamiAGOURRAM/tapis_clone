func main()
{
	const Int[] b;
	const Int blength;
	Int argmax = 0;

	Int i = 0;

	while(i < blength)
	{
	    if(b[argmax] < b[i])
	    {
	        argmax = i;
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
			(<= (b j) (b (argmax main_end)))
		)
	)
)
