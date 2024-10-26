#!/bin/bash

echo -n -e "Enter month : "
read month 

case $month in

1|jan|JAN|Jan) echo "Jan -> 31 days" ;;
2|feb) echo "Feb-> 28/29" ;;
3) echo "March -> 31" ;;
esac
