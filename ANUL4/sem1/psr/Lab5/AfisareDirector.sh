#!/bin/bash
if [ -d "$1" ]; then
    ls -R "$1"
else
    echo "$1 nu este un director"
fi
