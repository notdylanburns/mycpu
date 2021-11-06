#!/bin/bash

file="$1"

if [[ -z $file ]] ; then
    echo No file specified...
    echo Usage: create_roms.sh microcode_file
    exit 1
elif [[ -e $file ]] ; then
    python parse_csv.py $file
    echo "v2.0 raw" > bin/microcode.lsrom
    xxd -g 4 -c 4 -p bin/microcode.bin >> bin/microcode.lsrom

    truncate -s 128K bin/bios.bin
    echo "v2.0 raw" > bin/bios.lsrom
    xxd -g 2 -c 2 -p bin/bios.bin >> bin/bios.lsrom
else
    echo File $file doesn\'t exist
    exit 1
fi