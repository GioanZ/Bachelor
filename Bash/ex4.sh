#!/bin/bash

clear
n=0
i=0
while read riga
do
	for parola in $riga
	do
		lN=${#parola}
		if test $n -eq 0
		then
			pMax[0]=$parola
			lV=${#parola}
			n=1
		elif test $lN -gt $lV
		then
			unset pMax
			lV=$lN
			i=0
			pMax[0]=$parola
		elif test $lN -eq $lV
		then
			let i=i+1
			pMax[$i]=$parola
		fi
	done
done < "file.txt"

echo -e "lenMax: $lV \t parola: ${pMax[*]}"
