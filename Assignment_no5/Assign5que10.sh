#!/bin/bash

function msg ()

{
	echo "Hello Desd..."

}

function print_num ()
{
	echo "$1 $2"
}

print_num 10 20

function check_prime () 
{
	flag=0
		i=2
		while [ $i -lt $1 ]
			do
				if [ `expr $1 % $i` -eq 0 ]
					then 
						flag=1
						fi
						i=`expr $i +1`
						done

						echo $flag
}

res=$( check_prime 13 )
	echo "res = $res"

	if [ $res -eq 0 ]
	then 
	echo "prime"
	else
	echo "not prime"
	fi
