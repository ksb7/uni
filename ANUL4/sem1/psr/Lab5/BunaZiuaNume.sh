#!/bin/bash
if [ $# -eq 2 ]; then
    echo "Buna ziua, $1 $2"
elif [ $# -eq 0 ]; then
    echo "Buna ziua, $LOGNAME"
else
    echo "Utilizare: $0 [Nume Prenume]"
fi
