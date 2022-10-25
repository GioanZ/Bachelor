#!/bin/bash
n=1
while read row
do
	echo "Row $n: $row"
	let n=n+1
done < in.txt > out.txt

exit 0
