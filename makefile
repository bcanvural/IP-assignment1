CC=gcc

all: mysh1 mysh2 mysh3

mysh1: mysh1.o
	$(CC) -o mysh1 mysh1.o 


mysh2: mysh2.o
	$(CC) -o mysh2 mysh2.o

mysh3: mysh3.o
	$(CC) -o mysh3 mysh3.o
