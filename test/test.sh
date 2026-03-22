#!/bin/bash

if [[ "$#" -ne 2 ]]; then
    echo "Usage: "$0" <tests file> <program file>"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "Test run failed: "$1" not found"
    exit 1
fi

if [[ ! -f "$2" ]]; then
    echo "Test run failed: "$2" not found"
    exit 1
fi

echo "Test run started"
echo ""

expr=""
num=1

while IFS= read -r line || [[ -n "$line" ]]; do
    (echo "$line" | tr -d '\n') > tmp.txt
    expr=$("$2" tmp.txt)
    printf "%d\t%s -> %s\n" $num $line $expr
    echo ""
    ((num++))   
done < "$1"

echo "Test run ended"