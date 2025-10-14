#!/bin/bash
clear
if [ $# -eq 0 ]; then
    ls -l ~
else
    ls -l "$1"
fi
