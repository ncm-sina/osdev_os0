
TARGET=../../dist/kernel/kernel.bin

# Find all C source files in the current directory
SRCS = $(wildcard *.c)

# Generate object files from the source files
OBJS = $(patsubst %.c,%.o,$(SRCS))

all-kernel: 
	@echo "-----------------Building Kernel------------------" 
	make $(TARGET)


CFLAGS=  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS=  -ffreestanding -O2 -nostdlib

LINKS = $(wildcard ../include/*.o)

KERNEL_OBJS=\
pre_kernel.o\
kernel.o\

$(TARGET): $(KERNEL_OBJS) $(LINKS)
	i686-elf-gcc $(LFLAGS) -T ./linker.ld -o $@ $(KERNEL_OBJS) $(LINKS) -lgcc

all-build: ../dist/kernel/pre_kernel.o ../dist/kernel/kernel.o


%.o: %.c
	@echo "building c files"
	i686-elf-gcc $(CFLAGS) -I../include -c $< -o $@

pre_kernel.o: pre_kernel.s
	i686-elf-as $< -o $@

