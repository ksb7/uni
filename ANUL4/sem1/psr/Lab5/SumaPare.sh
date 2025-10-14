#!/bin/bash
i=2
s=0
c=0
while [ $c -lt 5 ]
do
    s=$((s + i))
    i=$((i + 2))
    c=$((c + 1))
done
echo "Suma primelor 5 numere pare este: $s"
