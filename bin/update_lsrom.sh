echo "v2.0 raw" > microcode.lsrom
xxd -g 4 -c 4 -p microcode.bin >> microcode.lsrom

truncate -s 128K bios.bin
echo "v2.0 raw" > bios.lsrom
xxd -g 2 -c 2 -p bios.bin >> bios.lsrom