CC=gcc

all: mysh1 mysh2

mysh1: mysh1.o
	$(CC) -o mysh1 mysh1.o 


mysh2: mysh2.o
	$(CC) $(CFLAGS) -o mysh2 mysh2.o
