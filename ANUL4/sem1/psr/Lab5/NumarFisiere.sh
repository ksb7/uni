#!/bin/bash
if [ -d "$1" ]; then
    echo "Cautare superficiala:"
    echo "Fisiere: $(find "$1" -maxdepth 1 -type f | wc -l)"
    echo "Directoare: $(find "$1" -maxdepth 1 -type d | wc -l)"

    echo "Cautare in profunzime:"
    echo "Fisiere: $(find "$1" -type f | wc -l)"
    echo "Directoare: $(find "$1" -type d | wc -l)"
else
    echo "$1 nu exista"
fi
