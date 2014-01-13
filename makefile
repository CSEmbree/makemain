CC=gcc
CFLAGS=-Wall
DEBUG=-g -DDBUG
SP=src/
MAIN=$(SP)mm.c


install: all

all: makemain

makemain: 
	$(CC) $(CFLAGS) $(MAIN) -o mm

debug:
	$(CC) $(DEBUG) $(CFLAGS) $(MAIN) -o mm

clean:
	rm -rf mm *.dSYM
