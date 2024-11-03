#!/bin/bash


read -p "Enter the name of the first file: " file1


if [[ ! -f "$file1" ]]; then
    echo "File '$file1' does not exist."
    exit 1
fi

read -p "Enter the name of the second file: " file2

touch "$file2"

while IFZ= read -r line; do
   
    echo "$line" | tr '[:lower:][:upper:]' '[:upper:][:lower:]' >> "$file2"
done < "$file1"

echo "Contents of '$file1' in reverse case have been appended to '$file2'."

