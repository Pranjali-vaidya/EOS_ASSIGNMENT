#!/bin/bash

echo -e -n "enter  num :"
read num

if [ $num -gt 0 ]
then 
echo "num  is a positive : $num"

elif [ $num -lt 0 ]
then
echo "num is a negative : $num"

else
echo "num is zero : $num"
fi

