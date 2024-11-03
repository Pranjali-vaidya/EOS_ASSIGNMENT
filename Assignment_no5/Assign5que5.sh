#!/bin/bash

echo -e -n "Enter Num1 :"
read n1

echo -e -n "Enter Num2 :"
read n2

echo -e -n "Enter Num3 :"
read n3

if [ $n1 -gt $n2 ]
then 
  
if [ $n1 -gt $n3 ]
then

echo "Num1 = $n1"

else

echo "Num3 = $n3"

fi

else

if [ $n2 -gt $n3 ]
then

echo "Num2 = $n2"

else

echo "Num3 = $n3"

fi
fi


