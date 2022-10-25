#!/bin/bash


if [ $# -ne 1 ]
then
  echo "Usage: $0 file"
  exit 1
fi

# we suppose that each line doesn't contain spaces
for line in `cat $1`
do
  filename=`basename $1 .txt`
  nc=`echo $line | wc -c` 
  echo $nc >> tmp.txt 
  echo "$line $nc" > $filename".out"
done

echo `sort -r -n tmp.txt | head -n 1`
echo `wc -l $1`

