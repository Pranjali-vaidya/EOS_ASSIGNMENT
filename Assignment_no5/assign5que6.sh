#!/bin/bash

echo -e -n "enter year : "
read year

if [ `expr $year % 4` -eq 0 -a `expr $year % 100` -ne 0 -o `expr $year % 400` -eq 0 ]
then
echo "leap"
else
echo "not leap"
fi
