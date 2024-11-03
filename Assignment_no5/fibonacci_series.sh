#!/bin/bash

fibonacci() {
    n=$1
    a=0
    b=1

    echo "Fibonacci series up to $n terms:"

    for (( i=0; i<n; i++ ))
    do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo # for a new line after the series
}
if [ $# -eq 0 ]; then
    echo "Usage: $0 <number_of_terms>"
    exit 1
fi

fibonacci $1

