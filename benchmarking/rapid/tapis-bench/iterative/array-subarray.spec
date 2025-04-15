func main()
{
	const Int[] array;
	const Int[] subarray;
	const Int m;
	const Int n;

	Int idx = 1-2;
  Int i = 0;
  while(i < m) {
    if(m - i >= n) {
      Int is_sub = 1;
      Int k = 0;
      while(is_sub == 1 && k < n) {
        if(array[i + k] != subarray[k]) {
          is_sub = 0;
        } else {
          skip;
        }
        k = k + 1;
      }
      if(is_sub == 1) {
        idx = i;
      } else {
        skip;
      }
    } else {
        skip;
    }
    i = i + 1;
  }
}

(conjecture
    (=>
        (and
            (> n 0)
            (> m 0)
            (<= n m)
        )
        (=>
            (not (= (idx main_end) (- 1 2)))
            (and
                (>= (idx main_end) 0)
                (forall ((j Int))
                    (=>
                        (and
                            (<= 0 j)
                            (< j n)
                        )
                        (= (subarray j) (array (+ (idx main_end) j)))
                    )
                )
            )
        )
    )
)
