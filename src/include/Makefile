
# TARGET=../../dist/kernel/kernel.bin

# Find all C source files in the current directory
SRCS = $(wildcard *.c)

# Generate object files from the source files
OBJS = $(patsubst %.c,%.o,$(SRCS))

all-includes: 
	@echo "-----------------Building Includes------------------" 
	make $(OBJS)


CFLAGS=  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS=  -ffreestanding -O2 -nostdlib


# $(TARGET): pre-kernel.o $(OBJS)
# 	@echo $(SRCS)
# 	@echo $(OBJS)
# 	i686-elf-gcc $(LFLAGS) -T ./linker.ld -o $@ $< $(OBJS) -lgcc

# all-build: ../dist/kernel/pre-kernel.o ../dist/kernel/kernel.o


%.o: %.c
	@echo "building c files"
	i686-elf-gcc $(CFLAGS) -I../include -c $< -o $@

# pre-kernel.o: pre-kernel.s
# 	i686-elf-as $< -o $@

