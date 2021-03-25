
ODIR=./bin
CONFIG=./config

OBJS=$(wildcard bin/*.o)

all: all-objects
	ld -m elf_i386 -T $(CONFIG)/link.ld -o $(ODIR)/kernel.bin $(OBJS)

	# Create iso dir for grub
	mkdir -p isodir/boot/grub
	cp $(ODIR)/kernel.bin isodir/boot/.
	cp $(CONFIG)/grub.cfg isodir/boot/grub/.
	grub-mkrescue -o kernel.iso isodir

all-objects:
	cd kernel && $(MAKE) all
	cd sys && $(MAKE) all
	cd drivers && $(MAKE) all

run:
	bochs

clean:
	rm -rf isodir
	rm -rf kernel.iso
	cd bin && rm -rf *.o *.bin 