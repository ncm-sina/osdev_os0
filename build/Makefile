
all:
	$(MAKE) -C ../src/kernel -f Makefile all-kernel
	make prepare-iso


init:
	mkdir -p ../dist/
	mkdir -p ../dist/drivers
	mkdir -p ../dist/kernel
	mkdir -p ../dist/lib
	
	

clean:
	rm ../dist -fr


prepare-iso:
	mkdir -p ../dist/isodir/boot/grub
	mkdir -p ../dist/isodir/kernel
	mkdir -p ../dist/isodir/drivers
	mkdir -p ../dist/isodir/images
	cp ../dist/kernel/kernel.bin ../dist/isodir/kernel/kernel.bin
	cp ../src/config/grub/grub.cfg ../dist/isodir/boot/grub/grub.cfg	


test-os:
	# ../../grub-2.12/grub-file --is-x86-multiboot ../dist/kernel.bin

include ../src/kernel/Makefile

