AS:=nasm
ASFLAGS:=-f elf
CFLAGS:=-m32
LDFLAGS:=-m32
CC:=/usr/bin/gcc
CXX:=g++
CXXFLAGS:=-m32
TARGETS:=main

.PHONY:clean

%.o:%.asm
	$(AS) $(ASFLAGS) $< 

all:clean $(TARGETS)

operations:
	$(AS) $(ASFLAGS) -d ELF_TYPE operations.asm -o operations.o

main: main.c operations
	$(CC) $(CFLAGS) main.c operations.o -o main


clean :
	rm -f *.o $(TARGETS)