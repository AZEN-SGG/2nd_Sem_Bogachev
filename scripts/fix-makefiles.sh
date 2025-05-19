#!/bin/bash
# Скрипт для авто-исправления Makefile'ов: удаляет -lssp, меняет .exe → .out и del → rm

find . -type f -name "Makefile" | while read -r file; do
    echo "Обрабатываю: $file"
        sed -i \
                -e 's/-lssp//g' \
                        -e 's/\.exe/\.out/g' \
                                -e 's/\<del\>/rm/g' \
                                        "$file"
                                        done

                                        echo "Готово!"

