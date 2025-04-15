func main()
{
  const Int[] array;
  const Int[] subarray;
  const Int m;
  const Int n;
  const Int idx;
  Int is_sub = 0;
  Int k = 0;
  if(idx + n < m) {
    is_sub = 1;
    while(is_sub == 1 && k < n) {
      if(array[idx + k] != subarray[k]) {
        is_sub = 0;
      } else {
        skip;
      }
      k = k + 1;
    }
  } else {
    skip;
  }
}

(conjecture
    (=>
        (and
            (> n 0)
            (> m 0)
            (<= n m)
            (<= 0 idx)
            (< idx m)
            )
	(forall ((j Int))
		(=>
			(and
				(<= 0 j)
				(< j n)
			)
			(= (subarray j) (array (+ idx j)))
		)
	)
	)
)
