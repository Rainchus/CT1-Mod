mkdir obj
mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/ct1.c
mv ct1.o obj/
armips asm/main.asm
n64crc "rom/ct1.mod.z64"