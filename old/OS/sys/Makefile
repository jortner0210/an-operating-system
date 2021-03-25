CC=gcc
ISYS=../sys
IDRIVERS=../drivers
IKERNEL=../kernel
CFLAGS=-I$(ISYS) -I$(IKERNEL) -I$(IDRIVERS)

ODIR=../bin

SRC=$(wildcard *.c)
HEADER=$(wildcard *.h)
OBJ = ${SRC:.c=.o}

all: ${OBJ} 

%.o: %.c $(HEADER)
	$(CC) -m32 -fno-pie -ffreestanding -c $< -o $(ODIR)/$@ $(CFLAGS)
