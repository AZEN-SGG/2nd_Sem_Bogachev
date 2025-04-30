script_name="$(basename "$0")"
mkdir -p tests

if [ "$#" -ne 2 ]; then
	echo "The number of parameters is less than 2"
	exit 1
fi

make

for (( k = 0 ; k < 7; k++ )); do 
	echo "------- K = $k -------"
	for (( a = -10 ; a < 11 ; a++ )); do 
		for (( b = $a ; b < 11 ; b++ )); do
			echo "a = $a b = $b Iter = 1000 ---"
			taskset -c $2 ./a0$1.out $a $b 1e-16 1000 $k
		done
	done
done >$(pwd)/tests/out_$script_name.log 2>$(pwd)/tests/err_$script_name.log
