#!/bin/bash

# Function to calculate gross salary
calculate_gross_salary() {
    basic_salary=$1
    da=$(echo "$basic_salary * 0.40" | bc -l)  # DA = 40% of basic salary
    hra=$(echo "$basic_salary * 0.20" | bc -l)  # HRA = 20% of basic salary
    gross_salary=$(echo "$basic_salary + $da + $hra" | bc -l)  # Gross Salary calculation

    echo "Gross Salary: $gross_salary"
}


read -p "Enter Basic Salary: " basic_salary


if ! [[ "$basic_salary" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
    echo "Invalid input. Please enter a numeric value."
    exit 1
fi

calculate_gross_salary $basic_salary

