#BullShit! Compiler Makefile
#Author: Joseph St. Pierre
#Year: 2018

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

CC = gcc

EXE = bs

C_FLAGS = -std=c99

local:
	$(CC) -c $(SRC)
	$(CC) $(C_FLAGS) -o $(EXE) $(OBJ)
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(EXE)

