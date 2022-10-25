#!/bin/bash
clear
#provo es in slide
# Using command line parameters in a script
echo "Ciao, $USER!"
echo "Il programma $0 e’ in run"
echo "Primo parametro: $1"
echo "Secondo parametro: $2"
echo "Numero dei parametri $#"
echo "Lista dei parametri: $*"
echo "Home directory: $HOME"
echo "Path: $PATH"

#ora comincia l'esercizio vero del lab
echo -e "\n"

case $# in
	0)
		echo devi mettere almeno un nome
		exit 1
		;;
	1)
		echo prosegui...
		#break #ma qua non serve
		;;
esac
#echo "my ID is 73535" | tr -d [:digit:]
#echo "Tecmint.com =>Linux-HowTos,Guides,Tutorials" | tr " " ":"
#chiama il programma: ./ex1.sh mcat
echo I diversi PATH:
for i in $(echo $PATH | tr ":" " ")
do
	echo $i
	if test -e $i/$1
	then
		echo -e "esiste\n"
		if [ -f $i/$1 ]
		then
			echo -e "è un file regolare\n"
		fi
	fi
done





exit 0
