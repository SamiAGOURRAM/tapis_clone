func main()
{
	const Int[] b;
	const Int blength;
	const Int v;

	Int i = 0;
    Int k = blength;
    Int idx = 1-2;
	while(i < blength && k > 0 && i <= k)
	{
		if(b[i] == v) {
            idx = i;
        } else {
            skip;
        }
        if(b[k - 1] == v) {
            idx = k - 1;
        } else {
            skip;
        }
		i = i + 1;
		k = k - 1;
	}
}

(conjecture
        (=>
        (> blength 0)
		(=>
			(not
			    (=
			        (idx main_end)
			        (- 1 2)))
			(=
			    (b (idx main_end))
			    v)
		)
		)
)
