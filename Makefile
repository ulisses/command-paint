# top-level rule to compile the whole program.
all: main.o

# program is made of several source files.
#prog: main.o
#	gcc main.o -Wall -o prog

# rule for file "main.o".
main.o: prog.c myio.c
	gcc prog.c myio.c -Wall -lm -o main.o

#rule for file "myio.o".
#myio.o: myio.c myio.h
#	gcc myio.c -lm -Wall -o myio.o

#rule for file "id.o"
#id.o: id.c id.h
#	gcc -Wall -c id.c
