func main()
{
	const Int[] b;
	const Int blength;
	const Int v;

	Int i = 0;
    Int idx = 1-2;
	while(i < blength)
	{
		if(b[i] == v) {
            idx = i;
        } else {
            skip;
        }
		i = i + 1;
	}
}

(conjecture
    (=> (> blength 0)
		(and
            (=>
                (not
                    (=
                        (idx main_end)
                        (- 1 2)))
                (=
                    (b (idx main_end))
                    v)
            )
		(=>
		    (=
			        (idx main_end)
			        (- 1 2))
		    (forall ((j Int))
		(=>
			(and
				(<= 0 blength)
				(<= 0 j)
				(< j blength)
			)
			(not (= (b j) v))
		)
	)
		)
		))
)

