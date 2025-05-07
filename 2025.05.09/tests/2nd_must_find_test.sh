script_name="$(basename "$0")"
mkdir -p tests

if [ "$#" -ne 1 ]; then
	echo "The number of parameters is not equal 1"
	exit 1
fi

make

for (( k = 0 ; k < 7; k++ )); do 
	echo "------- K = $k -------"
	for (( a = -100 ; a < 100 ; a++ )); do 
		echo "k = $k x_0 = "$(echo "$a / 10" | bc -l)" ---"
		./a0$1.out "$(echo "$a / 10" | bc -l)" 1e-14 $k
	done
done >$(pwd)/tests/out_$script_name.log 2>$(pwd)/tests/err_$script_name.log
