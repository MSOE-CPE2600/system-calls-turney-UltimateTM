CFLAGS=-c -g -Wall -Werror
LDFLAGS= -lm
SOURCES= finfo.c info.c pinfo.c pmod.c
EXECUTABLE= info
CC=gcc

all: info pinfo finfo pmod

info: info.o
	$(CC) -o info info.o

pinfo: pinfo.o
	$(CC) -o pinfo pinfo.o

finfo: finfo.o
	$(CC) -o finfo finfo.o

pmod: pmod.o
	$(CC) -o pmod pmod.o

clean:
	rm -f *.o info pinfo finfo pmod

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

