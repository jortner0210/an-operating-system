# Automatically  generate  lists  of  sources  using  wildcards.
C_SOURCES = $(wildcard  kernel/*.c kernel/sys/*.c drivers/*.c)
HEADERS = $(wildcard  kernel/*.h drivers/*.h)

# TODO: Make sources  dep on all  header  files.

# Convert  the *.c filenames  to *.o to give a list of  object  files  to  build
OBJ = ${C_SOURCES:.c=.o}

# Defaul  build  target
all: os-image to-bin

# Run  bochs  to  simulate  booting  of our  code.
run: all
	bochs

# This is the actual disk image that the computer loads
# A combination of compiled bootsector and kernel
os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

# This builds the binary of our kernel from two object files:
#	- the kernel_entry.asm, which jumps to main() in our kernel
#	- the compiled C kernel
kernel.bin: kernel/kernel_entry.o ${OBJ} 
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity, all C fils depend on all header files
%.o : %.c ${HEADERS}
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

# Assemble to kernel_entry
%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -I  "./boot/module" -o $@

to-bin:
	find ./kernel ./boot ./drivers -type f -name "*.o" -exec mv -t bin/ {} +
	find ./kernel ./boot ./drivers -type f -name "*.bin" -exec mv -t bin/ {} +
	mv ./kernel.bin bin/kernel.bin
	mv os-image bin/os-image
	
clean:
	rm -fr bin/*.bin bin/*.o bin/os-image
	rm -fr *.bin *.dis *.o os-image
	rm -fr  kernel/*.o boot/*.bin  drivers/*.o