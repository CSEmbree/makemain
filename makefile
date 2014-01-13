CC=gcc
CFLAGS=-c -Wall
SP=src/
MAIN=$(SP)mm.c


install: all

all: makemain

makemain: 
	$(CC) $(MAIN) $(OFILES) -o mm

clean:
	rm -rf mm
