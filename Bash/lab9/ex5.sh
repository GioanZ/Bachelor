#!/bin/bash
clear
if test $# -ne 1
then
	echo hai sbagliato
	echo consiglio: ./ex5.sh prova.in
	exit 1
fi

max=0
N=0
out=`basename $1 .in`".out"
echo $out
while read riga
do
	let N=N+1
	nR=${#riga}
	echo $N: $nR
	if test $max -lt $nR #se max < riga
	then
		max=$nR
	fi
done < $1 > $out

echo righe tot:	$N	caratteri max:	$max

exit 0
