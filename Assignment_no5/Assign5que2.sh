#!/bin/bash

while true; do
    echo "Menu:"
    echo "1. Date"
    echo "2. Cal"
    echo "3. Ls"
    echo "4. Pwd"
    echo "5. Exit"
    read -p "Choose an option (1-5): " choice

    case $choice in
        1)
            echo "Current Date and Time:"
            date
            ;;
        2)
            echo "Current Month Calendar:"
            cal
            ;;
        3)
            echo "Directory Contents:"
            ls
            ;;
        4)
            echo "Current Working Directory:"
            pwd
            ;;
        5)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose again."
            ;;
    esac
    echo ""
done

