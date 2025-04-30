script_name="$(basename "$0")"
iter="1000"
mkdir -p tests

if [ "$#" -ne 2 ]; then
	echo "The number of parameters is less than 2"
	exit 1
fi

make

for (( k = 3 ; k < 7; k++ )); do 
	echo "------- K = $k -------"
	for (( a = -100 ; a < -40 ; a++ )); do 
		for (( b = -9 ; b < 10 ; b++ )); do
			echo "a = $a b = $b Iter = $iter ---"
			sudo taskset -c $2 nice -n -20 ./a0$1.out "$(echo "$a / 10" | bc -l)" "$(echo "$b / 10" | bc -l)" 1e-16 $iter $k
		done
	done
	for (( a = -9 ; a < 10 ; a++ )); do 
		for (( b = 11 ; b < 100 ; b++ )); do
			echo "a = $a b = $b Iter = $iter ---"
			sudo taskset -c $2 nice -n -20 ./a0$1.out "$(echo "$a / 10" | bc -l)" "$(echo "$b / 10" | bc -l)" 1e-16 $iter $k
		done
	done
done >$(pwd)/tests/out_$script_name.log 2>$(pwd)/tests/err_$script_name.log
