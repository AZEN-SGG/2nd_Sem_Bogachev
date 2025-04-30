#!/bin/bash

# Проверяем, передан ли файл как аргумент
if [ $# -eq 0 ]; then
    echo "Использование: $0 <имя_файла>"
    exit 1
fi

input_file="$1"

# Проверяем существование файла
if [ ! -f "$input_file" ]; then
    echo "Ошибка: файл '$input_file' не существует"
    exit 1
fi

# Ищем строки с " Res = " и выводим их
grep " Res = " "$input_file" > found_str.log

