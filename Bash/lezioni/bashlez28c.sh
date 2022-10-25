#!/bin/bash
if [ $# -lt 2 ] ; then
	echo -n "Values: "
	read n1 n2
else
	n1=$1
	n2=$2
fi

i=0
k=0
while [ $i -lt $n1 ] ; do
	j=0
	while [ $j -lt $n2 ] ; do
		echo -n "$k "
	 	let k=k+1
		let j=j+1
	done
	let i=i+1
	echo
done

exit 0
