#!/bin/bash

file="$1"
rp=`realpath $0`
rootdir=`dirname $rp`

if [[ -z $file ]] ; then
    echo No file specified...
    echo Usage: create_roms.sh microcode_file output_file
    exit 1
elif [[ -e $file ]] ; then
    python $rootdir/parse_csv.py $file $rootdir/bin/microcode.bin
    echo "v2.0 raw" > $rootdir/bin/microcode.lsrom
    xxd -g 4 -c 4 -p $rootdir/bin/microcode.bin >> $rootdir/bin/microcode.lsrom

    truncate -s 128K $rootdir/bin/bios.bin
    echo "v2.0 raw" > $rootdir/bin/bios.lsrom
    xxd -g 2 -c 2 -p $rootdir/bin/bios.bin >> $rootdir/bin/bios.lsrom
else
    echo File $file doesn\'t exist
    exit 1
fi