script_name="$(basename "$0")"

iter="1000"
eps="1e-14"

if [ "$#" -ne 1 ]; then
	echo "Не указан как параметр номер программы"
	exit 1
fi

num=$(printf "%02d" "$1")
prog="a$num.out"

mkdir -p tests

if [ -f Makefile ]; then
	echo "Компиляция..."
	make clean
	make
fi

if [ ! -f $prog ]; then
	echo "Отсутствует исполняемый файл... [$prog]"
	echo "Завершение..."
	exit 2
fi

outlog="$(pwd)/tests/out_a${num}_$script_name.log"
errlog="$(pwd)/tests/err_a${num}_$script_name.log"

rm -f "$outlog" "$errlog"

echo "Тест запущен..."

i=2

for (( k = 3 ; k < 7; k++ )); do 
	for (( a = -100 ; a < -40 ; a++ )); do 
		for (( b = -9 ; b < 10 ; b++ )); do
			x="$(echo "$a / 10" | bc -l)"
			y="$(echo "$b / 10" | bc -l)"
			cmd="./$prog $poly_deg $x $y $eps $iter $k"
			echo "$cmd"
			echo "$i $(eval "$cmd")"
			((i+=2))
		done
	done
	for (( a = -9 ; a < 10 ; a++ )); do 
		for (( b = 11 ; b < 100 ; b++ )); do
			x="$(echo "$a / 10" | bc -l)"
			y="$(echo "$b / 10" | bc -l)"
			cmd="./$prog $poly_deg $x $y $eps $iter $k"
			echo "$cmd"
			echo "$i $(eval "$cmd")"
			((i+=2))
		done
	done
done >$outlog 2>$errlog

echo "Тест записан в $outlog"
echo "Ошибки записаны в $errlog"
echo "Тест завершен"

