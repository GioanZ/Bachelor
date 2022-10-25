#!/bin/bash

ping -c 1 www.google.com | grep '1 received'
if [ $? -eq 0 ]
then
	echo "connesso"
else
	echo "non connesso"
fi
