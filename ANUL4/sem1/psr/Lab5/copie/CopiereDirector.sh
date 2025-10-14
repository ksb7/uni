#!/bin/bash
if [ -d "$1" ]; then
    cp -r "$1" copie
    echo "Directorul $1 a fost copiat in copie/"
else
    echo "Directorul $1 nu exista"
fi
