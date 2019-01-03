#!/bin/bash

PROJECT_NAME=TDCT
INPUT_DIRECTORY=$1
ROOT_FILE=$2

if ! [ -d $INPUT_DIRECTORY ]
then
	echo Error: Wrong input directroy!
	exit
elif ! [ -e "$INPUT_DIRECTORY/$INPUT_FILE" ]
then
	echo Error: Root file missing!
	exit
fi

cmake ..
make

cd $INPUT_DIRECTORY
if ! [ -d results ]
then
	mkdir results
fi

cd -

./TDCT $INPUT_DIRECTORY $ROOT_FILE > "$INPUT_DIRECTORY/results/output.txt"

