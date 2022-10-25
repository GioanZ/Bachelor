#!/bin/bash

x=1
lenM=0
for parola in $(ps -e)
do
        if test $x -eq 4
        then
                x=0
                lenN=${#parola}
                if [ $lenN -gt $lenM ]
                then
                        lenM=$lenN
                        pM=$parola
                fi
        fi
        let x=x+1
done
echo -e "$lenM\t$pM"

