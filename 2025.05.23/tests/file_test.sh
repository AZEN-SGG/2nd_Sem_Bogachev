script_name="$(basename "$0")"
script_path="$(realpath "$0")"
script_dir="$(dirname "$script_path")"

maxpr="100"

mkdir -p tests

if [ -f Makefile ]; then
	echo "Компиляция..."
	make clean
	make
fi

outlog="$(pwd)/tests/out_$script_name.log"
errlog="$(pwd)/tests/err_$script_name.log"

rm -f "$outlog" "$errlog"

echo "Тест запущен..."

for npr in {1..10} ; do
	num=$(printf "%02d" "$npr")
	prog="a$num.out"
	if [ -f $prog ]; then
		for ntst in {1..10} ; do
			cmd="./$prog $maxpr $script_dir/inputs/input_$ntst.txt"
			echo "$cmd"
			eval "$cmd"
		done
	fi
done >$outlog 2>$errlog

echo "Тест записан в $outlog"
echo "Ошибки записаны в $errlog"
echo "Тест завершен"

make clean

