echo "v2.0 raw" > microcode.lsrom
hexdump -e '4/1 "%02x" "\n"' microcode.bin >> microcode.lsrom

echo "v2.0 raw" > bios.lsrom
hexdump -e '2/1 "%02x" "\n"' bios.bin >> bios.lsrom