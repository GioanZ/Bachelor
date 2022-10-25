#!/bin/bash
echo "Number: $#"
echo $0
for x in $*
do
	echo -n $x" "
done
echo $0 
