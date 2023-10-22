#!/bin/bash

# Проверка наличия аргументов
if [ $# -ne 3 ]; then
  echo "Использование: $0 <путь_к_файлу> <строка_для_замены> <замена>"
  exit 1
fi

# Исходный файл (путь от корневой директории)
file_path="$1"

# Строка для замены
search_string="$2"

# Замена
replace_string="$3"

# Полный путь к файлу от корневой директории
full_file_path="$file_path"

# Проверка существования файла
if [ ! -f "$full_file_path" ]; then
  echo "Файл $file_path не найден."
  exit 1
fi

# Создание резервной копии файла
backup_file="$full_file_path.bak"
cp "$full_file_path" "$backup_file"

# Замена подстроки в файле
sed -i "s/$search_string/$replace_string/g" "$full_file_path"

# Вычисление размера файла в байтах
file_size=$(stat -c %s "$full_file_path")

# Вычисление SHA-суммы файла (SHA-256)
sha_sum=$(shasum -a 256 "$full_file_path" | awk '{print $1}')

# Добавление записи в файл журнала
log_entry="$file_path — $file_size — $(date) — $sha_sum — sha-256"
echo "$log_entry" >> "$PWD/files.log"
