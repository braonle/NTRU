MAKE = make
CC = g++
LIBPATH = lib
SRC = Source.cpp
OBJ = ${SRC:.cpp=.o}
CFLAGS +=-std=c++11 -c -W -Wall -g -fpic
LDFLAGS = -std=c++11 -W -Wall -g -L ${LIBPATH}
LIBFLG = -lntru
INC = include/
TARGET = ./tmp.out
LIB = lib/libntru.so

all: ${TARGET}

${TARGET}: ${OBJ} ${LIB}
	${CC} -I ${INC} ${LDFLAGS} ${OBJ} ${LIBFLG} -o tmp.out
	
.cpp.o:
	${CC} ${CFLAGS} -I ${INC} $< -o $@ 

${LIB}:
	${MAKE} -C ./src all	
	
clean:
	${MAKE} -C ./src clean
	rm -f *.o
install:
	cp lib/* /usr/local/lib
uninstall:
	rm -f /usr/local/lib/libntru.so*

update:
	${MAKE} -C ./src all	
delete:
	rm -r lib/*

.PHONY: exec, library, clean, install, delete
