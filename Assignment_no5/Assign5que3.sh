#!/bin/bash

# Prompt the user for input
read -p "Enter the name of the file or directory: " name

# Check if the name exists
if [ -e "$name" ]; then
    # Check if it's a file
    if [ -f "$name" ]; then
        # Display the file size
        size=$(stat -c%s "$name")
        echo "It's a file. Size: $size bytes."
    # Check if it's a directory
    elif [ -d "$name" ]; then
        # Display the contents of the directory
        echo "It's a directory. Contents:"
        ls "$name"
    else
        echo "It's neither a regular file nor a directory."
    fi
else
    echo "The specified name does not exist."
fi

