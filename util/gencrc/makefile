# makefile for gencrc
CXX ?= g++

CC := $(CXX)
BINDIR = /usr/local/bin
SRC    = ../../../src
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic
LDLIBS  = -lm

all        : gencrc genxor genmsk
gencrc     : gencrc.o
genxor     : genxor.o
genmsk     : genmsk.o

clean:
	rm -f gencrc genxor genmsk *.o

test:
	./gencrc -16 > crc16.cpp
	./gencrc -24 > crc24.cpp
	./genxor > xor.cpp
	./genmsk > msk.cpp
