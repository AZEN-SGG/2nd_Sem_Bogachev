#!/bin/bash

# Скрипт для автотестирования задач 1-10 с однонаправленным списком строк
# Исполняемые файлы: a01.out, a02.out, ..., a10.out
# Ошибки сохраняются в error.txt

# Установка прав на исполнение
chmod +x a*.out

echo "Компилирую программу:"
make clean
make
echo "Программа скомпилирована"

# Очищаем файлы результатов и ошибок
> res.txt
> error.txt

# Функция для вывода разделителя
print_separator() {
    echo "=================" >> res.txt
}

# Функция для записи ошибки
log_error() {
    local task_num=$1
    local test_file=$2
    local message=$3
    
    echo "Задача: $task_num | Файл: $test_file | Ошибка: $message" >> error.txt
}

# Функция для запуска теста с обработкой ошибок
run_test() {
    local task_num=$1
    local max_print=$2
    local filename=$3
    local binary="./a$(printf "%02d" $task_num).out"
    
    # Проверяем существование исполняемого файла
    if [ ! -f "$binary" ]; then
        echo "Исполняемый файл $binary не найден!" >> res.txt
        log_error $task_num $filename "Исполняемый файл $binary не найден"
        return 1
    fi

    # Проверяем существование входного файла
    if [ ! -f "$filename" ]; then
        echo "Входной файл $filename не найден!" >> res.txt
        log_error $task_num $filename "Входной файл не найден"
        return 1
    fi

    # Запускаем программу и перехватываем ошибки
    echo "Запуск: $binary $max_print $filename" >> res.txt
    output=$(timeout 10s $binary $max_print $filename 2>&1)
    status=$?

    case $status in
        0)
            # Успешное выполнение
            echo "$output" >> res.txt
            ;;
        136|139)
            # Ошибка SEGFAULT (SIGSEGV)
            echo "ОШИБКА: SEGFAULT (нарушение сегментации)" >> res.txt
            log_error $task_num $filename "SEGFAULT (нарушение сегментации)"
            ;;
        8|136|137|139)
            # FPE (SIGFPE) или другие сигналы
            echo "ОШИБКА: FPE (ошибка вычисления с плавающей точкой)" >> res.txt
            log_error $task_num $filename "FPE (ошибка вычисления с плавающей точкой)"
            ;;
        124)
            # Таймаут
            echo "ОШИБКА: Таймаут выполнения (программа зависла)" >> res.txt
            log_error $task_num $filename "Таймаут выполнения (программа зависла)"
            ;;
        *)
            # Другие ошибки
            echo "ОШИБКА: Программа завершилась с кодом $status" >> res.txt
            log_error $task_num $filename "Программа завершилась с кодом $status"
            ;;
    esac
}

test="test"

# Создаем тестовые файлы с данными
create_test_files() {
    # Тестовый файл 1 - несколько строк разной длины
    echo -e "apple\nbanana\napple\ncherry\ndate\napple\nfig\ngrape" > ${test}1.txt
    
    # Тестовый файл 2 - строки с повторениями
    echo -e "one\none\ntwo\ntwo\ntwo\nthree\nfour\nfour" > test2.txt
    
    # Тестовый файл 3 - возрастающая последовательность
    echo -e "a\nb\nc\nd\ne\nf\ng\nh" > test3.txt
    
    # Тестовый файл 4 - убывающая последовательность
    echo -e "h\ng\nf\ne\nd\nc\nb\na" > test4.txt
    
    # Тестовый файл 5 - случайные строки
    echo -e "cat\ndog\ncat\nbird\nfish\nbird\ndog\ncat" > test5.txt
    
    # Тестовый файл 6 - пустой файл
    echo -n "" > test6.txt
    
    # Тестовый файл 7 - одна строка
    echo "single" > test7.txt
    
    # Тестовый файл 8 - длинные строки
    echo -e "very_long_string_1234567890\nshort\nmedium_length_string_123" > test8.txt
}

delete_test_files() {
	for n in {1..8} ; do
		rm "${test}$n.txt"
	done ;
}

# Создаем тестовые файлы
create_test_files

# Запуск тестов для всех задач (1-10)
for task_num in {1..10}; do
    print_separator
    echo "=== ЗАДАЧА $task_num ===" >> res.txt
    print_separator
    
    # Тестируем на всех тестовых файлах
    for test_file in test{1..8}.txt; do
        echo "Тестируемый файл: $test_file" >> res.txt
        echo "Максимум выводимых элементов: 5" >> res.txt
        
        run_test $task_num 5 $test_file
        echo "" >> res.txt # Добавляем пустую строку между тестами
    done
    
    echo "" >> res.txt # Добавляем пустую строку между задачами
done

delete_test_files
make clean

# Выводим количество ошибок
error_count=$(wc -l < error.txt)
echo "Найдено ошибок: $error_count" | tee -a res.txt

