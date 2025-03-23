build-os: ../dist/kernel/kernel.bin

../dist/kernel/kernel.bin: ../dist/kernel/pre-kernel.o ../dist/kernel/kernel.o
	i686-elf-gcc -T ../src/kernel/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

all-build: ../dist/kernel/pre-kernel.o ../dist/kernel/kernel.o

../dist/kernel/kernel.o: ../src/kernel/kernel.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra


../dist/kernel/pre-kernel.o: ../src/kernel/pre-kernel.s
	i686-elf-as $< -o $@
