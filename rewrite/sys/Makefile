CC=gcc
ISYS=../sys
CFLAGS=-I$(ISYS)

ODIR=../bin

SRC=$(wildcard *.c)
HEADER=$(wildcard *.h)
OBJ = ${SRC:.c=.o}

all: ${OBJ} 

%.o: %.c $(HEADER)
	$(CC) -m32 -fno-pie -ffreestanding -c $< -o $(ODIR)/$@ $(CFLAGS)
