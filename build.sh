#!/bin/bash

rp=`realpath $0`
rootdir=`dirname $rp`
curl -L "https://docs.google.com/spreadsheets/d/19egtyPgxQ730lNQn6o9-pgWj9gaJw375gotFo6NXyeU/export?format=csv&id=19egtyPgxQ730lNQn6o9-pgWj9gaJw375gotFo6NXyeU&gid=1787194635" > $rootdir/Microcode.csv
$rootdir/create_roms.sh $rootdir/Microcode.csv
make -C $rootdir/d16-asm