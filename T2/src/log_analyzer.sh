#!/bin/bash

# Проверка наличия аргумента
if [ $# -ne 1 ]; then
  echo "Использование: $0 <путь_к_файлу_журнала>"
  exit 1
fi

# Путь к файлу журнала (путь от корневой директории)
log_file="$1"

# Полный путь к файлу журнала от корневой директории
full_log_file="$log_file"

# Проверка существования файла журнала
if [ ! -f "$full_log_file" ]; then
  echo "Файл журнала $log_file не найден."
  exit 1
fi

# Извлечение информации из файла журнала
total_entries=$(cat "$full_log_file" | wc -l)
unique_files=$(cat "$full_log_file" | awk '{print $1}' | sort | uniq | wc -l)
#changed_files=$(cat "$full_log_file" | awk '{print $4}'| uniq | wc -l)
changed_files=$(cat "$full_log_file" | grep -c "sha-256")

# Вывод результатов
echo "$total_entries $unique_files $changed_files"
