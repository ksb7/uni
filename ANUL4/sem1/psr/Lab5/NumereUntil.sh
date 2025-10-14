#!/bin/bash
i=1
sum=0
until [ $i -gt $1 ]; do
    echo $i
    sum=$((sum+i))
    i=$((i+1))
done
echo "Media = $((sum/$1))"
