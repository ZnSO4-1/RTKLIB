# makefile for pos2kml
CXX ?= g++

CC := $(CXX)
BINDIR = /usr/local/bin
SRC    = ../../../src
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -I$(SRC) -DTRACE
LDLIBS  = -lm -lrt

pos2kml    : pos2kml.o convkml.o solution.o geoid.o rtkcmn.o preceph.o

pos2kml.o  : ../pos2kml.cpp
	$(CXX) -c $(CXXFLAGS) ../pos2kml.cpp
convkml.o  : $(SRC)/convkml.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/convkml.cpp
solution.o : $(SRC)/solution.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/solution.cpp
geoid.o    : $(SRC)/geoid.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/geoid.cpp
rtkcmn.o   : $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
preceph.o  : $(SRC)/preceph.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/preceph.cpp

pos2kml.o  : $(SRC)/rtklib.h
convkml.o  : $(SRC)/rtklib.h
solution.o : $(SRC)/rtklib.h
geoid.o    : $(SRC)/rtklib.h
rtkcmn.o   : $(SRC)/rtklib.h
preceph.o  : $(SRC)/rtklib.h

install:
	cp pos2kml $(BINDIR)

clean:
	rm -f pos2kml pos2kml.exe *.o
