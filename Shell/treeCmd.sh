#!/bin/bash

function Red()
{
    echo -e "\033[31m$1\033[0m"
}

function Green()
{
    echo -e "\033[32m$1\033[0m"
}

function Blue()
{
    echo -e "\033[34m$1\033[0m"
}

function searchDir()
{
   for file in $(ls -al $1 | awk -F " " '/^d/  { print $NF }')
   do
        if [ "$file" == "." ]
        then
            #echo "$2 $file"
            continue
        elif [ "$file" == ".." ]
        then
            #echo "$2 $file"
            continue
        else
            tempFlag="|___"
            Blue "$2 $file"
            searchDir "$1/$file" "$tempFlag $2"
        fi
    done
    for file in $(ls -al $1 | awk -F " " '/^[a-c e-s u-z -]/  { print $NF }')
    do
        if [ -x "$1/$file" ]
        then
            Green "$2 $file"
        else
            echo "$2 $file"
        fi
    done
}


if [ -d $1 ]
then
    listPath="$1"
else
    listPath=""
fi

Blue $listPath

#cd $listPath || exit 1
#cd -

#tree
curPath=$(pwd)
childFile="|___"

searchDir $listPath  $childFile

echo "finish"
