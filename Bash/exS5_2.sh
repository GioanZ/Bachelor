#!/bin/bash

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
if [ $# -ne 1 ]
then
	echo devi mettere ./ex nomeExe2
	echo hai messo $#, cioè: $* FINE
	exit 1 
fi

echo $( $1 )

