# makefile for str2str
CXX ?= g++

CC := $(CXX)
BINDIR = /usr/local/bin
SRC    = ../../../src

# for beagleboard
#CTARGET= -mfpu=neon -mfloat-abi=softfp -ffast-math
CTARGET=

OPTION = -DENAGLO -DENAGAL -DENAQZS -DENACMP -DTRACE -DNFREQ=3 -DNEXOBS=3
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -Wno-unused-but-set-variable -I$(SRC) $(OPTION) $(CTARGET) -g
LDLIBS  = -lm -lrt -lpthread

all        : str2str
str2str    : str2str.o stream.o rtkcmn.o solution.o sbas.o geoid.o
str2str    : rcvraw.o novatel.o ublox.o ss2.o crescent.o skytraq.o gw10.o javad.o
str2str    : nvs.o binex.o rt17.o rtcm.o rtcm2.o rtcm3.o rtcm3e.o preceph.o streamsvr.o

str2str.o  : ../str2str.cpp
	$(CXX) -c $(CXXFLAGS) ../str2str.cpp
stream.o   : $(SRC)/stream.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/stream.cpp
streamsvr.o: $(SRC)/streamsvr.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/streamsvr.cpp
rtkcmn.o   : $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
solution.o : $(SRC)/solution.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/solution.cpp
sbas.o     : $(SRC)/sbas.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/sbas.cpp
geoid.o    : $(SRC)/geoid.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/geoid.cpp
rcvraw.o   : $(SRC)/rcvraw.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcvraw.cpp
novatel.o  : $(SRC)/rcv/novatel.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/novatel.cpp
ublox.o    : $(SRC)/rcv/ublox.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/ublox.cpp
ss2.o      : $(SRC)/rcv/ss2.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/ss2.cpp
crescent.o : $(SRC)/rcv/crescent.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/crescent.cpp
skytraq.o  : $(SRC)/rcv/skytraq.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/skytraq.cpp
gw10.o     : $(SRC)/rcv/gw10.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/gw10.cpp
javad.o    : $(SRC)/rcv/javad.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/javad.cpp
nvs.o      : $(SRC)/rcv/nvs.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/nvs.cpp
binex.o    : $(SRC)/rcv/binex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/binex.cpp
rt17.o     : $(SRC)/rcv/rt17.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcv/rt17.cpp
rtcm.o     : $(SRC)/rtcm.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm.cpp
rtcm2.o    : $(SRC)/rtcm2.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm2.cpp
rtcm3.o    : $(SRC)/rtcm3.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm3.cpp
rtcm3e.o   : $(SRC)/rtcm3e.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtcm3e.cpp
preceph.o  : $(SRC)/preceph.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/preceph.cpp

str2str.o  : $(SRC)/rtklib.h
stream.o   : $(SRC)/rtklib.h
streamsvr.o: $(SRC)/rtklib.h
rtkcmn.o   : $(SRC)/rtklib.h
solution.o : $(SRC)/rtklib.h
sbas.o     : $(SRC)/rtklib.h
geoid.o    : $(SRC)/rtklib.h
rcvraw.o   : $(SRC)/rtklib.h
novatel.o  : $(SRC)/rtklib.h
ublox.o    : $(SRC)/rtklib.h
ss2.o      : $(SRC)/rtklib.h
crescent.o : $(SRC)/rtklib.h
skytraq.o  : $(SRC)/rtklib.h
gw10.o     : $(SRC)/rtklib.h
javad.o    : $(SRC)/rtklib.h
nvs.o      : $(SRC)/rtklib.h
binex.o    : $(SRC)/rtklib.h
rt17.o     : $(SRC)/rtklib.h
rtcm.o     : $(SRC)/rtklib.h
rtcm2.o    : $(SRC)/rtklib.h
rtcm3.o    : $(SRC)/rtklib.h
rtcm3e.o   : $(SRC)/rtklib.h
preceph.o  : $(SRC)/rtklib.h

install:
	cp str2str $(BINDIR)

#DEVICE=ttyACM0
DEVICE=ttyS1:115200:8:n:1:off
#DEVICE=ttyUSB0:115200:8:n:1:off

test1:
	./str2str -in serial://$(DEVICE) -out file://test1.out -t 2

test2:
	./str2str -in serial://$(DEVICE) -out tcpsvr://:2102 -c ../../../data/oem4_raw_10hz.cmd -t 5

test3:
	./str2str -in serial://$(DEVICE) -out ntrips://:sesam@localhost:8000/BUCU0 -c ../../../data/oem4_raw_10hz.cmd -t 5

test4:
	./str2str -in ../oem6_20121107.gps#nov -out oem6_20121107.rtcm3#rtcm3 -sta 123 -msg "1077(10),1087(10),1097(10),1107(10),1117(10),1019,1020"

test5:
	./str2str -in ../oem6_20121107.gps#nov -out oem6_20121107_gal.rtcm3#rtcm3 -msg "1097(10)"

test6:
	./str2str -in serial://ttyS54:115200#nov -out tcpsvr://:2103#rtcm3 -c ../../../data/oem4_raw_10hz.cmd

clean:
	rm -f str2str str2str.exe *.o *.out *.trace

