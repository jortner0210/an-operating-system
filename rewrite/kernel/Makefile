CC=gcc
IDRIVERS=../drivers
ISYS=../sys
CFLAGS=-I$(IDRIVERS) -I$(ISYS) 

ODIR=../bin

SRC=$(wildcard *.c)
HEADER=$(wildcard *.h)
OBJ = ${SRC:.c=.o}

all: kasm ${OBJ} 

kasm:
	nasm -f elf32 kernel.asm -o $(ODIR)/kasm.o

%.o: %.c $(HEADER)
	$(CC) -m32 -fno-pie -ffreestanding -c $< -o $(ODIR)/$@ $(CFLAGS)
