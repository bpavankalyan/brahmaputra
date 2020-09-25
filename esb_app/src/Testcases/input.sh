#!/bin/bash

m=$#

if [ "$1" = "bmd" ]; then
	while [ -n "$2" ]; do
		echo "$2"
		curl --insecure -F "bmd_file=@"$2"" https://localhost:8888/bmd
		shift
	done
elif [ "$1" = "get-status" ]; then
	while [ -n "$2" ]; do
		echo "$2"
		curl -k  https://localhost:8888/get-status?messageid="$2"
		shift
	done
else
	echo "NONE"

fi


