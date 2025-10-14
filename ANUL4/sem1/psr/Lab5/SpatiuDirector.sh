#!/bin/bash
dir=${1:-$HOME}

echo "Spatiul total al directorului $dir:"
du -sh "$dir"

echo
echo "Spatiul fiecarui subdirector sortat descrescator:"
du -sh "$dir"/* 2>/dev/null | sort -hr
