script_name="$(basename "$0")"
prog="6"

iter="1000"
poly_deg="10"
eps="1e-14"

mkdir -p tests

if [ -f Makefile ]; then
	echo "Компиляция..."
	make clean
	make
fi

if [ ! -f a0$prog.out ]; then
	echo "Отсутствует исполняемый файл... [a0$prog.out]"
	echo "Завершение..."
	exit 1
fi

outlog="$(pwd)/tests/out_a0${prog}_$script_name.log"
errlog="$(pwd)/tests/err_a0${prog}_$script_name.log"

rm -f $outlog $errlog

echo "Тест запущен..."

for (( k = 3 ; k < 7; k++ )); do 
	for (( a = -100 ; a < -40 ; a++ )); do 
		for (( b = -9 ; b < 10 ; b++ )); do
			x="$(echo "$a / 10" | bc -l)"
			y="$(echo "$b / 10" | bc -l)"
			cmd="./a0$prog.out $poly_deg $x $y $eps $iter $k"
			echo "$cmd"
			$cmd
		done
	done
	for (( a = -9 ; a < 10 ; a++ )); do 
		for (( b = 11 ; b < 100 ; b++ )); do
			x="$(echo "$a / 10" | bc -l)"
			y="$(echo "$b / 10" | bc -l)"
			cmd="./a0$prog.out $poly_deg $x $y $eps $iter $k"
			echo "$cmd"
			$cmd
		done
	done
done >$outlog 2>$errlog

echo "Тест записан в $outlog"
echo "Ошибки записаны в $errlog"
echo "Тест завершен"

