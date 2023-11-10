ASM = nasm

.PHONY: all floppy_image kernel bootloader clean always tools_fat

all: floppy_image tools_fat

floppy_image: build/main_floppy.img

build/main_floppy.img: bootloader kernel
	dd if=/dev/zero of=build/main_floppy.img bs=512 count=2880
	mkfs.fat -F 12 -n "BILEPTEROS" build/main_floppy.img
	dd if=build/bootloader.bin of=build/main_floppy.img conv=notrunc
	mcopy -i build/main_floppy.img build/kernel.bin "::kernel.bin"
	mcopy -i build/main_floppy.img test.txt "::test.txt"

build/main.bin: src/main.asm
	$(ASM) src/main.asm -f bin -o build/main.bin 

bootloader: build/bootloader.bin
	$(ASM) src/bootloader/boot.asm -f bin -o build/bootloader.bin
 
kernel: build/kernel.bin

build/kernel.bin: always
	$(ASM) src/kernel/main.asm -f bin -o build/kernel.bin

build/bootloader.bin: always
	$(ASM) src/bootloader/boot.asm -f bin -o build/bootloader.bin

tools_fat: build/tools/fat
build/tools/fat: always tools/fat/fat.c
	mkdir -p build/tools
	gcc -g -o build/tools/fat tools/fat/fat.c

always:
	mkdir -p build

run:
	qemu-system-i386 -fda build/main_floppy.img

clean:
	rm -rf build/*	