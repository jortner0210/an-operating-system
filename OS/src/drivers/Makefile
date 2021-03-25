IDRIVERS=../drivers
ISYS=../kernel/sys
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
INCLUDES=-I$(IDRIVERS) -I$(ISYS)

ODIR=../../build

SRC=$(wildcard *.c)
HEADER=$(wildcard *.h)
OBJ = ${SRC:.c=.o}

BUILDS=$(wildcard build/*.o)

build:
	mkdir build
	./build.sh

all: $(OBJ) 
	i686-elf-ld -g -relocatable $(BUILDS) -o $(ODIR)/drivers.o

clean:
	rm -rf build

%.o: %.c $(HEADER)
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c $< -o ./build/$@
