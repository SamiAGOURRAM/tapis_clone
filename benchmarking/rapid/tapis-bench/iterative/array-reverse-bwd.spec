func main()
{
	const Int[] b;
	const Int blength;
	Int[] a;

    Int k = blength;
	while(k > 0)
	{
        a[k - 1] = b[blength - k];
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
			(= (a main_end j) (b (- blength (+ j 1))))
		)
	)
)
