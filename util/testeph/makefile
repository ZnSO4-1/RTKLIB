# makefile for diffeph dumpssr
CXX ?= g++

CC := $(CXX)
SRC    = ../../src
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -I$(SRC) -DTRACE -DENAQZS -DENAGLO -DEXTLEX
LDFLAGS = -lm

all        : diffeph dumpssr

diffeph    : rtkcmn.o ephemeris.o sbas.o rinex.o preceph.o rtcm.o rtcm2.o rtcm3.o
diffeph    : ionex.o pntpos.o ppp.o ppp_ar.o stec.o qzslex.o
dumpssr    : rtkcmn.o preceph.o rtcm.o rtcm2.o rtcm3.o

rtkcmn.o   : $(SRC)/rtklib.h $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
ephemeris.o: $(SRC)/rtklib.h $(SRC)/ephemeris.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ephemeris.cpp
sbas.o     : $(SRC)/rtklib.h $(SRC)/sbas.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/sbas.cpp
rinex.o    : $(SRC)/rtklib.h $(SRC)/rinex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rinex.cpp
preceph.o  : $(SRC)/rtklib.h $(SRC)/preceph.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/preceph.cpp
rtcm.o     : $(SRC)/rtklib.h $(SRC)/rtcm.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm.cpp
rtcm2.o    : $(SRC)/rtklib.h $(SRC)/rtcm2.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm2.cpp
rtcm3.o    : $(SRC)/rtklib.h $(SRC)/rtcm3.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm3.cpp
ionex.o    : $(SRC)/rtklib.h $(SRC)/ionex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ionex.cpp
pntpos.o   : $(SRC)/rtklib.h $(SRC)/pntpos.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/pntpos.cpp
ppp.o      : $(SRC)/rtklib.h $(SRC)/ppp.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp.cpp
ppp_ar.o   : $(SRC)/rtklib.h $(SRC)/ppp_ar.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp_ar.cpp
stec.o     : $(SRC)/rtklib.h $(SRC)/stec.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/stec.cpp
qzslex.o   : $(SRC)/rtklib.h $(SRC)/qzslex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/qzslex.cpp

install:
	cp -f diffeph.exe /usr/local/bin
	cp -f dumpssr.exe /usr/local/bin

clean:
	rm -f *.o *.stackdump *.trace *.out *.exe

