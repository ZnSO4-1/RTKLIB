# makefile for ppp_local
CXX ?= g++

CC := $(CXX)
RTKLIBDIR=../../src

CXXFLAGS = -Wall -O3 -I$(RTKLIBDIR) -DTRACE
LDFLAGS = -lm

BIN = genstec

all        : $(BIN)
genstec    : genstec.o rtkcmn.o ephemeris.o preceph.o sbas.o rinex.o
#gengrid    : gengrid.o rtkcmn.o stec.o preceph.o

rtkcmn.o   : $(RTKLIBDIR)/rtklib.h $(RTKLIBDIR)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/rtkcmn.cpp
ephemeris.o: $(RTKLIBDIR)/ephemeris.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/ephemeris.cpp
preceph.o  : $(RTKLIBDIR)/preceph.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/preceph.cpp
sbas.o     : $(RTKLIBDIR)/sbas.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/sbas.cpp
rinex.o    : $(RTKLIBDIR)/rinex.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/rinex.cpp
stec.o     : $(RTKLIBDIR)/stec.cpp
	$(CXX) -c $(CXXFLAGS) $(RTKLIBDIR)/stec.cpp

OBSDIR=/proj/data_gsi/2011
NAVDIR=/proj/data/2011
STA=0225

OBS=$(OBSDIR)/001/$(STA)0010.11o $(OBSDIR)/002/$(STA)0020.11o $(OBSDIR)/003/$(STA)0030.11o
NAV=$(NAVDIR)/001/brdc0010.11n $(NAVDIR)/002/brdc0020.11n $(NAVDIR)/003/brdc0030.11n

test1:
	./genstec $(OBS) $(NAV) -a igs05.atx -o iono_$(STA).stec

test2:
	./gengrid "stec/iono_*.stec" -d stec_grid

install:
	cp -f $(BIN) /usr/local/bin

clean:
	rm -f $(BIN) *.o *.trace

