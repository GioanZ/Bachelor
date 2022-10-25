#!/bin/bash

clear

case $# in
	0)
		echo  devi mettere X secondi e U utente
		exit 1
		;;
	1)
		echo devi mettere X secondi e U utente
		exit 1
		;;
esac

while [  1 -eq 1 ]
do
	w=`who | grep $1`
	echo $w
	echo $?
	if [ $? -ne 0 ]
	then
		echo non loggato
	else
		echo loggato
	fi
	sleep $2
done

echo fine
