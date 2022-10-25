#!/bin/bash

if [ $# -ne 1 ]
then
	echo sbagliato il numero di input di chiamata $#
	exit 1
fi

while read riga
do
	# Calcola il numero di parole in una linea
	n=$(echo $riga | wc -w)
# Se la linea ha un numero dispari di parole, coverti la linea in minuscolo
	if [ $[$n%2] -eq 1 ]; then
		echo $riga | tr [A-Z] [a-z]
	elif [ $[$n%2] -eq 0 ]; then
		echo $riga | tr [a-z] [A-Z]
	fi
done < $1
