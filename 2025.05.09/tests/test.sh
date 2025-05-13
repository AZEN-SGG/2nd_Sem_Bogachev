#!/bin/bash

chmod +x *.out

# Очищаем файл результатов
> res.txt

# Функция для вывода разделителя
print_separator() {
    echo "=================" >> res.txt
}

# Функция для форматированного вывода входных данных
format_input() {
    local task_num=$1
    local line=($2)
    
    case $task_num in
        1|2|3)
            echo "x=${line[0]} h=${line[1]} k=${line[2]}" >> res.txt
            ;;
        4|5|6|7)
            echo "a=${line[0]} b=${line[1]} n=${line[2]} k=${line[3]}" >> res.txt
            ;;
        8|9)
            echo "a=${line[0]} b=${line[1]} e=${line[2]} k=${line[3]}" >> res.txt
            ;;
        10|11)
            echo "a=${line[0]} e=${line[1]} k=${line[2]}" >> res.txt
            ;;
        12)
            echo "a=${line[0]} b=${line[1]} e=${line[2]} k1=${line[3]} k2=${line[4]}" >> res.txt
            ;;
    esac
}

# Функция для запуска теста с обработкой ошибок
run_test() {
    local task_num=$1
    local line=$2
    local binary="./a$(printf "%02d" $task_num).out"
    
    # Проверяем существование исполняемого файла
    if [ ! -f "$binary" ]; then
        echo "Исполняемый файл $binary не найден!" >> res.txt
        return 1
    fi

    # Запускаем программу и перехватываем ошибки
    output=$(timeout 100s $binary $line 2>&1)
    status=$?

    case $status in
        0)
            # Успешное выполнение
            echo "$output" >> res.txt
            ;;
        136)
            # Ошибка SEGFAULT (SIGSEGV)
            format_input $task_num "$line"
            echo "ОШИБКА: SEGFAULT (нарушение сегментации)" >> res.txt
            ;;
        136|139)
            # Ошибка SEGFAULT (SIGSEGV)
            format_input $task_num "$line"
            echo "ОШИБКА: SEGFAULT (нарушение сегментации)" >> res.txt
            ;;
        8|136|137|139)
            # FPE (SIGFPE) или другие сигналы
            format_input $task_num "$line"
            echo "ОШИБКА: FPE (ошибка вычисления с плавающей точкой)" >> res.txt
            ;;
        124)
            # Таймаут
            format_input $task_num "$line"
            echo "ОШИБКА: Таймаут выполнения (программа зависла)" >> res.txt
            ;;
        *)
            # Другие ошибки
            format_input $task_num "$line"
            echo "ОШИБКА: Программа завершилась с кодом $status" >> res.txt
            ;;
    esac
}

# Запуск тестов для задач 1-3
for i in {1..3}; do
    print_separator
    echo "=== TASK $i ===" >> res.txt
    print_separator
    
    while read -r line || [[ -n "$line" ]]; do
        [ -z "$line" ] && continue # Пропускаем пустые строки
        format_input $i "$line"
        run_test $i "$line"
        echo "" >> res.txt # Добавляем пустую строку между тестами
    done < tests1-3.txt
    
    echo "" >> res.txt # Добавляем пустую строку между задачами
done

# Запуск тестов для задач 4-7
for i in {4..7}; do
    print_separator
    echo "=== TASK $i ===" >> res.txt
    print_separator
    
    while read -r line || [[ -n "$line" ]]; do
        [ -z "$line" ] && continue
        format_input $i "$line"
        run_test $i "$line"
        echo "" >> res.txt
    done < tests4-7.txt
    
    echo "" >> res.txt
done

# Запуск тестов для задач 8-9
for i in {8..9}; do
    print_separator
    echo "=== TASK $i ===" >> res.txt
    print_separator
    
    while read -r line || [[ -n "$line" ]]; do
        [ -z "$line" ] && continue
        format_input $i "$line"
        run_test $i "$line"
        echo "" >> res.txt
    done < tests8-9.txt
    
    echo "" >> res.txt
done

# Запуск тестов для задач 10-11
for i in {10..11}; do
    print_separator
    echo "=== TASK $i ===" >> res.txt
    print_separator
    
    while read -r line || [[ -n "$line" ]]; do
        [ -z "$line" ] && continue
        format_input $i "$line"
        run_test $i "$line"
        echo "" >> res.txt
    done < tests10-11.txt
    
    echo "" >> res.txt
done

# Запуск тестов для задачи 12
print_separator
echo "=== TASK 12 ===" >> res.txt
print_separator
while read -r line || [[ -n "$line" ]]; do
    [ -z "$line" ] && continue
    format_input 12 "$line"
    run_test 12 "$line"
    echo "" >> res.txt
done < tests12.txt
