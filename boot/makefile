KDIR = ../kernel

# $^ - is substitued with all of a target's dependency files
# $< is the  first  dependancy  and $@ is the  target  file

all: os-image

run: all
	bochs

os-image: boot_sect.bin kernel.bin
	cat $^ > os-image

# Build the kernel binary
kernel.bin: kernel_entry.o kernel.o
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
kernel.o: ${KDIR}/kernel.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

# Build the kernel entry object file
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@


boot_sect.bin: boot_sect.asm
	nasm $< -f bin -I './modules' -o $@

clean: 
	rm -f *.o *.bin