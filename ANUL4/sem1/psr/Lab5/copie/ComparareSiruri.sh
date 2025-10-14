#!/bin/bash
echo "Introdu primul sir: "
read s1
echo "Introdu al doilea sir: "
read s2

if [ "$s1" = "$s2" ]; then
    echo "Cele doua siruri de caractere sunt egale"
else
    echo "Cele doua siruri de caractere sunt diferite"
fi
