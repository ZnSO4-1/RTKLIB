# makefile for rtkrcv
CXX ?= g++

CC := $(CXX)
BINDIR = /usr/local/bin
SRC    = ../../../src

# for beagleboard
#CTARGET= -mfpu=neon -mfloat-abi=softfp -ffast-math
CTARGET= -DENAGLO -DENAQZS -DENACMP -DNFREQ=3

CXXFLAGS = -Wall -O3 -std=c++11 -pedantic -Wno-unused-but-set-variable -I$(SRC) -I.. -DTRACE $(CTARGET) -g
LDLIBS  = -lm -lrt -lpthread

all        : rtkrcv
rtkrcv     : rtkrcv.o vt.o rtkcmn.o rtksvr.o rtkpos.o geoid.o solution.o lambda.o
rtkrcv     : sbas.o stream.o rcvraw.o rtcm.o preceph.o options.o pntpos.o ppp.o ppp_ar.o
rtkrcv     : novatel.o ublox.o ss2.o crescent.o skytraq.o gw10.o javad.o nvs.o binex.o
rtkrcv     : rt17.o ephemeris.o rinex.o ionex.o rtcm2.o rtcm3.o rtcm3e.o qzslex.o

rtkrcv.o   : ../rtkrcv.cpp
	$(CXX) -c $(CXXFLAGS) ../rtkrcv.cpp
vt.o       : ../vt.cpp
	$(CXX) -c $(CXXFLAGS) ../vt.cpp
rtkcmn.o   : $(SRC)/rtkcmn.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkcmn.cpp
rtksvr.o   : $(SRC)/rtksvr.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtksvr.cpp
rtkpos.o   : $(SRC)/rtkpos.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rtkpos.cpp
geoid.o    : $(SRC)/geoid.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/geoid.cpp
solution.o : $(SRC)/solution.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/solution.cpp
lambda.o   : $(SRC)/lambda.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/lambda.cpp
sbas.o     : $(SRC)/sbas.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/sbas.cpp
stream.o   : $(SRC)/stream.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/stream.cpp
rcvraw.o : $(SRC)/rcvraw.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rcvraw.cpp
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
options.o  : $(SRC)/options.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/options.cpp
pntpos.o   : $(SRC)/pntpos.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/pntpos.cpp
ppp.o      : $(SRC)/ppp.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp.cpp
ppp_ar.o   : $(SRC)/ppp_ar.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ppp_ar.cpp
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
ephemeris.o: $(SRC)/ephemeris.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ephemeris.cpp
rinex.o    : $(SRC)/rinex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/rinex.cpp
ionex.o    : $(SRC)/ionex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/ionex.cpp
qzslex.o   : $(SRC)/qzslex.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/qzslex.cpp

rtkrcv.o   : $(SRC)/rtklib.h ../vt.h
rtkcmn.o   : $(SRC)/rtklib.h
rtksvr.o   : $(SRC)/rtklib.h
rtkpos.o   : $(SRC)/rtklib.h
geoid.o    : $(SRC)/rtklib.h
solution.o : $(SRC)/rtklib.h
lambda.o   : $(SRC)/rtklib.h
sbas.o     : $(SRC)/rtklib.h
rcvraw.o   : $(SRC)/rtklib.h
rtcm.o     : $(SRC)/rtklib.h
rtcm2.o    : $(SRC)/rtklib.h
rtcm3.o    : $(SRC)/rtklib.h
rtcm3e.o   : $(SRC)/rtklib.h
preceph.o  : $(SRC)/rtklib.h
options.o  : $(SRC)/rtklib.h
pntpos.o   : $(SRC)/rtklib.h
ppp.o      : $(SRC)/rtklib.h
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
ephemeris.o: $(SRC)/rtklib.h
rinex.o    : $(SRC)/rtklib.h
ionex.o    : $(SRC)/rtklib.h
qzslex.o   : $(SRC)/rtklib.h

install:
	cp rtkrcv $(BINDIR)

test1:
	./rtkrcv -t 4 -m 52001 -t 4

test2:
	./rtkrcv -p 2105 -m 52001

test3:
	./rtkrcv -o ../rtk_pb.conf

clean:
	rm -f rtkrcv rtkrcv.exe rtkrcv.nav *.o *.out *.trace

