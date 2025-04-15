func main()
{
	Int[] b;
	const Int blength;

	Int i = 0;
    Int swapped = 1;
    Int j = 0;
    Int tmp = 0;
	while(swapped == 1)
	{
	    swapped = 0;
	    j = 0;
	    while(j < blength)
	    {
            if(b[j - 1] > b[j]) {
                tmp = b[j];
                b[j] = b[j - 1];
                b[j - 1] = tmp;
                swapped = 1;
            } else {
                skip;
            }
            j = j + 1;
	    }
	}
}

(conjecture
	(forall ((k Int)(l Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 k)
				(<= k l)
				(< l blength)
			)
			(<= (b main_end k) (b main_end l))
		)
	)
)
