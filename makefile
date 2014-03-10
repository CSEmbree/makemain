CC=gcc -std=c99
CFLAGS=-Wall
DEBUG=-g -DDBUG

#path to c and h files
SP=src/

#makemain c file with path 
MAIN=$(SP)mm.c

#Executable destination
EDEST=bin


install: all

all: makemain

makemain: general
	@$(CC) $(CFLAGS) $(MAIN) -o $(EDEST)/makemain
	@chmod u+x $(EDEST)/makemain

debug: general
	@$(CC) $(DEBUG) $(CFLAGS) $(MAIN) -o $(EDEST)/makemain
	@chmod u+x $(EDEST)/makemain

general:
	@sh setup.sh

	
clean:
	@rm -rf $(EDEST)/makemain $(EDEST)/makemain.dSYM >/dev/null 2>/dev/null
	@rm /usr/local/bin/mm >/dev/null 2>/dev/null

rebuild: clean install
