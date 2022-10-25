#!/bin/bash
clear
for f in `find $1 -type f`
do
	name=`basename $f`
	echo name: $name
	nameUp=`echo $name| tr [a-z] [A-Z]`
	echo nameUp: $nameUp
       	pathNew=`dirname $f`
	echo pathNew: $pathNew
	mv $f $pathNew/$nameUp
done
