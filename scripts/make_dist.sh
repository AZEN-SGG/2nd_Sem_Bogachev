#!/bin/bash

# Проверка аргументов
if [ "$#" -lt 2 ]; then
    echo "Использование: $0 <кол-во задач> <номера задач...>"
    exit 1
fi

count=$1
shift
tasks=("$@")

if [ "${#tasks[@]}" -ne "$count" ]; then
    echo "Ошибка: количество задач не совпадает с указанным числом"
    exit 1
fi

# Папка назначения
dest_dir="./dist/Krivoruchenko_SK"
mkdir -p "$dest_dir" || { echo "Не удалось создать $dest_dir"; exit 1; }

# Для отката, если что-то пойдёт не так
copied_files=()

cleanup_and_exit() {
    echo "Ошибка: $1"
    echo "Удаляю скопированные файлы..."
    for file in "${copied_files[@]}"; do
        rm -f "$file"
    done
    exit 1
}

replace_in_file() {
	local file="$1"
	local num="$2"

	sed -i -E "s|([\"'])solve\.h\1|\1solve_${num}.h\1|g" "$file"
}

# Проход по задачам
for num in "${tasks[@]}"; do
    folder=$(printf "%02dEx" "$num")
    if [ ! -d "$folder" ]; then
        cleanup_and_exit "Папка $folder не найдена"
    fi

    for file in main.c solve.c solve.h; do
        src="$folder/$file"
        if [ ! -f "$src" ]; then
            cleanup_and_exit "Файл $src не найден"
        fi

        base="${file%.*}"
        ext="${file##*.}"
        dest_file="$dest_dir/${base}_${folder:0:2}.$ext"

        cp "$src" "$dest_file" || cleanup_and_exit "Ошибка копирования $src"
        copied_files+=("$dest_file")
	if [[ "$file" == "main.c" || "$file" == "solve.c" ]]; then
		replace_in_file "$dest_file" "${folder:0:2}"
	fi
    done
done

echo "Все файлы успешно скопированы в $dest_dir"

