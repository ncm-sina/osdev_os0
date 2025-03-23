
all: build-os test-os prepare-iso

prepare-iso:
	mkdir -p ../dist/isodir/boot/isolinux
	mkdir -p ../dist/isodir/drivers
	mkdir -p ../dist/isodir/images
	mkdir -p ../dist/isodir/kernel
	
	cp ../dist/kernel.bin ../dist/isodir/kernel/kernel.bin
	cp ../src/config/isolinux/* ../dist/isodir/boot/isolinux -fr


test-os:
	# ../../grub-2.12/grub-file --is-x86-multiboot ../dist/kernel.bin


build-os: ../dist/kernel.bin

../dist/kernel.bin: ../dist/boot.o ../dist/kernel.o
	i686-elf-gcc -T ../src/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

all-build: ../dist/boot.o ../dist/kernel.o

../dist/kernel.o: ../src/kernel.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


../dist/boot.o: ../src/boot.s
	i686-elf-as $< -o $@

init:
	mkdir -p ../dist/

clean:
	rm ../dist -fr
