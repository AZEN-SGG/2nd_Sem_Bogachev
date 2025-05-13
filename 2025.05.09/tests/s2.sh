for stud in *_??
do
    cd $stud
    #echo > a01.txt
    #echo > a02.txt
    #echo > $studa03.txt
    for tsk in a01 a02 a03
    do
	echo > ../$stud$tsk.txt
	for x in -1 0 5 7
	do
	    for ((k=0; k < 7; k = k + 1))
	    do
		echo -n "$x 1e-5  $k   " >> ../$stud$tsk.txt
		./$tsk.out $x 1e-5 $k >> ../$stud$tsk.txt
		echo -n "$x 1e-9  $k   " >> ../$stud$tsk.txt
		./$tsk.out $x 1e-9 $k >> ../$stud$tsk.txt
		echo -n "$x 1e-12 $k   " >> ../$stud$tsk.txt
		./$tsk.out $x 1e-12 $k >> ../$stud$tsk.txt
	    done
	done
    done

    for tsk in a04 a05 a06 a07
    do
	echo > ../$stud$tsk.txt
	for AA in -5 -1 0 5 8
	do
	    for BB in -5 -1 0 5 8
	    do
		for NN in 0 3 5 7 10 100 
		do
		    for ((k=0; k < 7; k = k+1))
		    do
			echo -n "$AA $BB $NN $k   " >> ../$stud$tsk.txt
			./$tsk.out $AA $BB $NN $k >> ../$stud$tsk.txt
		    done
		done
	    done
	done
    done
    echo "$stud 1-7"

    for tsk in a08 a09
    do
	echo "$stud $tsk"
	echo > ../$stud$tsk.txt
	for AA in -5 -1 0 5 8
	do
	    for BB in -5 -1 0 5 8
	    do
		echo "A = $AA B = $BB"
		for EP in 1e-2 1e-9 1e-17
		do
		    for ((k=0; k < 7; k = k+1))
		    do
			echo -n "$AA $BB $EP $k   " >> ../$stud$tsk.txt
			./$tsk.out $AA $BB $EP $k >> ../$stud$tsk.txt
			echo $tsk: $AA $BB $EP $k
		    done
		done
	    done
	done
    done

    for tsk in a10 a11
    do
	echo "$stud $tsk"
	echo > ../$stud$tsk.txt
	for AA in -1 0 5 7
	do
	    for EP in 1e-3 1e-7 1e-17
	    do
		echo "$stud $tsk $AA $EP"
		for ((k=0; k < 7; k = k + 1))
		do
		    echo -n "$AA $EP $k   " >> ../$stud$tsk.txt
		    ./$tsk.out $AA $EP $k >> ../$stud$tsk.txt
		    echo $tsk: $AA $EP $k
		done
	    done
	done
    done
    
    tsk=a12
    echo > ../$stud$tsk.txt
    for AA in -5 0 8
    do
	for BB in -5 0 8
	do
	    for EP in 1e-2 1e-7
	    do
		echo "$stud $tsk $EP"
		for ((kx=0;kx < 7; kx = kx+1))
		do
		    for ((ky=0; ky < 7; ky = ky+1))
		    do
			echo $tsk: $AA $BB $EP $kx $ky
			echo -n " $AA $BB $EP $kx $ky   " >> ../$stud$tsk.txt
			./a12.out $AA $BB $EP $kx $ky >> ../$stud$tsk.txt
		    done
		done
	    done
	done
    done


    cd ..
done




for stud1 in *_??
do
    for stud2 in *_??
    do
	echo > $stud1$stud2.txt
	for tsk in a01 a02 a03 a04 a05 a06 a07 a08 a09 a10 a11 a12
	do
	    echo "###################################################" >>  $stud1$stud2.txt
	    echo "DIFF TSK = $tsk" >> $stud1$stud2.txt
	    diff $stud1$tsk.txt $stud2$tsk.txt >> $stud1$stud2.txt
	    echo "###################################################" >>  $stud1$stud2.txt

	done
    done
done









