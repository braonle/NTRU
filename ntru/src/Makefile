CFLAGS +=-std=c++11 -c -W -Wall -fPIC -O2
NAME = libntru.so.1
LDFLAGS = -std=c++11 -shared -Wl,-soname,${NAME}
CC = g++

SRC +=Numbers.cpp
SRC +=Polinom.cpp
SRC +=Parameters.cpp
SRC +=BitStream.cpp
SRC +=Encryption.cpp
SRC +=NTRULib.cpp
SRC +=Decryption.cpp

INC = ../include
LIBNAME = libntru.so.1.0.1 
LIB = ../lib
LIBPATH = ${LIB}/${LIBNAME}

OBJ = ${SRC:.cpp=.o}

all: ${LIBPATH}

${LIBPATH}: ${OBJ}
	${CC} -I ${INC} ${LDFLAGS} ${OBJ} -o $@	
	ln -sf ${LIBNAME} ${LIB}/${NAME}
	ln -sf ${LIBNAME} ${LIB}/libntru.so
	
.cpp.o: 
	${CC} -I ${INC} ${CFLAGS} $<

clean:
	rm -f *.o 

.PHONY: all, clean
