#!/bin/bash


if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename=$1

if [ -e "$filename" ]; then

    modification_time=$(stat -c %y "$filename")

    echo "The last modification time of '$filename' is: $modification_time"
else
    echo "File '$filename' does not exist."
fi

