CC=gcc
FLAGS= -lpthread
JFLAGS = -g
JC = javac
ALL = mysh1 mysh2 mysh3 syn1 syn2 synthread1 synthread2



all: mysh1 mysh2 mysh3 syn1 syn2 synthread1 synthread2

build: all javaprograms

mysh1: mysh1.o
	$(CC) -o mysh1 mysh1.o 


mysh2: mysh2.o
	$(CC) -o mysh2 mysh2.o

mysh3: mysh3.o
	$(CC) -o mysh3 mysh3.o

syn1: syn1.o
	$(CC) -o syn1 syn1.o

syn2: syn2.o
	$(CC) -o syn2 syn2.o

synthread1: synthread1.o
	$(CC) -o synthread1 synthread1.o $(FLAGS)

synthread2: synthread2.o
	$(CC) -o synthread2 synthread2.o $(FLAGS)


.SUFFIXES: .java .class
.java.class:
		$(JC) $(JFLAGS) $*.java

CLASSES = \
		syn1.java \
		syn2.java \
		ConsoleSyn1.java \
		ConsoleSyn2.java \
		mThreadSyn1.java \
		mThreadSyn2.java 


javaprograms: $(CLASSES:.java=.class)

clean:
	$(RM) *.class *.o $(ALL)