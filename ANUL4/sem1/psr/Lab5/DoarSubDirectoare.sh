#!/bin/bash
if [ -d "$1" ]; then
    for f in "$1"/*; do
        [ -d "$f" ] && echo "$f"
    done
else
    echo "$1 nu este un director"
fi
