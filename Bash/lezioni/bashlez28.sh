#!/bin/bash
n=1
for i in $* ; do
	echo "par # $n = $i"
	let n=n+1
done
